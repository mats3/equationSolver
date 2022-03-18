# ------------------------------ Prefferences ------------------------------
application_name = equationSolver

compiler = gcc

extern_lib =
extern_inc =

unit_test_lib = -lunicki

# [static] or [dynamic]
lib_type = static
# --------------------------------------------------------------------------
ifeq ($(lib_type),static)
lib_typ = .a
lib_command = ar rcs
endif
ifeq ($(lib_type),dynamic)
lib_typ = .so
lib_command = $(compiler) -shared -fpic
endif

cflags = $(compiler) -g -Wall

sub_dirs = $(filter-out $(wildcard src/*.c) $(wildcard src/*.h),$(wildcard src/*))
objdirs = $(patsubst src/%,obj/%,$(sub_dirs))

sublibs_path = $(patsubst obj/%,bin/lib%$(lib_typ),$(objdirs))
sublibs = $(addprefix -l,$(notdir $(sub_dirs)))

sub_srcs = $(wildcard src/*/*.c)
sub_objs = $(patsubst src/%.c,obj/%.o,$(sub_srcs))

srcs = $(wildcard src/*.c)
objs = $(patsubst src/%.c,obj/%.o,$(srcs))

tests_srcs = $(wildcard tests/*.c)
tests_objs = $(patsubst tests/%.c,tests/bin/%,$(tests_srcs))

bin = bin/$(application_name)

ifeq ($(shell uname -s),Linux)
# ------------------------------ Linux System ------------------------------
all: gen_subdirs compile libs link

compile: $(objs) $(sub_objs)

obj/%.o: src/%.c
	$(cflags) -c $< -o $@

libs: $(sublibs_path)

bin/lib%$(lib_typ): obj/%/*.o
	$(lib_command) -o $@ $^

link: $(bin)

$(bin): $(objs) $(sub_objs) 
	$(cflags) $(objs) -Lbin $(sublibs) $(extern_lib) -o $@

# Tests
test: $(tests_objs)
	$(foreach x,$(tests_objs),./$(x))

tests/bin/%: tests/%.c all
	gcc -o $@ $< $(filter-out obj/main.o,$(objs)) $(sub_objs) $(unit_test_lib)

# End Tests

install: test 
	@echo "Are You Sure To Install (Y,N)"; \
	read x; \
	if [ "$$x" = "y" ]; then \
		sudo cp $(bin) /usr/bin/$(application_name); \
		echo sudo cp $(bin) /usr/bin/$(application_name); \
	fi

# --------------------------------------------------------------------------
else
# ------------------------------ Windows System ----------------------------
all: gen_subdirs compile link

compile: $(objs) $(sub_objs)

obj/%.o: src/%.c
	$(cflags) -c $< -o $@

link: $(bin)

$(bin): $(objs)
	$(cflags) $(objs) $(sub_objs) -o $@
# --------------------------------------------------------------------------
endif

gen_subdirs:
	@for i in $(objdirs) ; do \
		if [ -d "$(i)" ] ; then \
			echo all done; \
		else \
			mkdir -p $(foreach i,$(objdirs),$(i)); \
		fi \
	done
	@if [ -d "./obj" ] ; then \
		echo all done; \
	else \
		mkdir -p obj; \
	fi

run: all
	./$(bin) $(a)

clean:
	rm obj -r
	rm bin/*

init:
	mkdir src
	mkdir bin
	mkdir -p tests/bin

print:
	@echo sub_dirs $(sub_dirs)
	@echo objdirs: $(objdirs)
	@echo sublibs_path: $(sublibs_path)
	@echo sublibs: $(sublibs)
	@echo sub_srcs: $(sub_srcs)
	@echo sub_objs: $(sub_objs)
	@echo srcs: $(srcs)
	@echo objs: $(objs)
	@echo tests_srcs $(tests_srcs)
	@echo tests_objs $(tests_objs)
