#include<unicki.h>
#include"../src/formula/node.h"
#include"../src/formula/formula.h"

void formulaTest(char *s, char *r) {
	test(s) {
		node_t *received = createEquation(s);
		assertStrEq(r, getFormatList(received));
	}
}

_testSection_

suite("src/formula") {
	suite("formula.h") {
		suite("addition") {
			formulaTest("a+b", "(+ab)");
			formulaTest("a+b+c", "(+abc)");
		}_end;
		suite("subtraction") {
			/*
			test("-a+b") {
				node_t *received = createEquation("-a");
				assertStrEq("(+(-a)b)", getFormatList(received));
			}
			*/
			formulaTest("a-b", "(-ab)");
			formulaTest("a-b-c", "(-abc)");
		}_end;
		suite("multiplication") {
			test("a*b") {
				node_t *received = createEquation("a*b");
				assertStrEq("(*ab)", getFormatList(received));
			}
			test("a*b*c") {
				node_t *received = createEquation("a*b*c");
				assertStrEq("(*abc)", getFormatList(received));
			}
		}_end;
		suite("division") {
			test("a/b") {
				node_t *received = createEquation("a/b");
				assertStrEq("(/ab)", getFormatList(received));
			}
			test("a/b/c") {
				node_t *received = createEquation("a/b/c");
				assertStrEq("(/abc)", getFormatList(received));
			}
		}_end;
		suite("addition & subtraction") {
			test("a+b-c") {
				node_t *received = createEquation("a+b-c");
				assertStrEq("(+a(-bc))", getFormatList(received));
			}
			test("b-c+a") {
				node_t *received = createEquation("b-c+a");
				assertStrEq("(+(-bc)a)", getFormatList(received));
			}
			test("a+b-c+d") {
				node_t *received = createEquation("a+b-c+d");
				assertStrEq("(+a(-bc)d)", getFormatList(received));
			}
			test("a-b+c-d") {
				node_t *received = createEquation("a-b+c-d");
				assertStrEq("(+(-ab)(-cd))", getFormatList(received));
			}
		}_end;
		suite("multiplication & division") {
			test("a*b/c") {
				node_t *received = createEquation("a*b/c");
				assertStrEq("(*a(/bc))", getFormatList(received));
			}
			test("b/c*a") {
				node_t *received = createEquation("b/c*a");
				assertStrEq("(*(/bc)a)", getFormatList(received));
			}
			test("a*b/c*d") {
				node_t *received = createEquation("a*b/c*d");
				assertStrEq("(*a(/bc)d)", getFormatList(received));
			}
			test("a/b*c/d") {
				node_t *received = createEquation("a/b*c/d");
				assertStrEq("(*(/ab)(/cd))", getFormatList(received));
			}
		}_end;
		suite("addition & multiplication") {
			test("a+b*c") {
				node_t *received = createEquation("a+b*c");
				assertStrEq("(+a(*bc))", getFormatList(received));
			}
			test("b*c+a") {
				node_t *received = createEquation("b*c+a");
				assertStrEq("(+(*bc)a)", getFormatList(received));
			}
			test("a+b*c+d") {
				node_t *received = createEquation("a+b*c+d");
				assertStrEq("(+a(*bc)d)", getFormatList(received));
			}
			test("a*b+c*d") {
				node_t *received = createEquation("a*b+c*d");
				assertStrEq("(+(*ab)(*cd))", getFormatList(received));
			}
		}_end;
		suite("subtraction & division") {
			test("a-b/c") {
				node_t *received = createEquation("a-b/c");
				assertStrEq("(-a(/bc))", getFormatList(received));
			}
			test("b/c-a") {
				node_t *received = createEquation("b/c-a");
				assertStrEq("(-(/bc)a)", getFormatList(received));
			}
			test("a-b/c-d") {
				node_t *received = createEquation("a-b/c-d");
				assertStrEq("(-a(/bc)d)", getFormatList(received));
			}
			test("a/b-c/d") {
				node_t *received = createEquation("a/b-c/d");
				assertStrEq("(-(/ab)(/cd))", getFormatList(received));
			}
		}_end;
		suite("addition & division") {
			test("a+b/c") {
				node_t *received = createEquation("a+b/c");
				assertStrEq("(+a(/bc))", getFormatList(received));
			}
			test("b/c+a") {
				node_t *received = createEquation("b/c+a");
				assertStrEq("(+(/bc)a)", getFormatList(received));
			}
			test("a+b/c+d") {
				node_t *received = createEquation("a+b/c+d");
				assertStrEq("(+a(/bc)d)", getFormatList(received));
			}
			test("a/b+c/d") {
				node_t *received = createEquation("a/b+c/d");
				assertStrEq("(+(/ab)(/cd))", getFormatList(received));
			}
		}_end;
		suite("subtraction & multiplication") {
			test("a-b*c") {
				node_t *received = createEquation("a-b*c");
				assertStrEq("(-a(*bc))", getFormatList(received));
			}
			test("b*c-a") {
				node_t *received = createEquation("b*c-a");
				assertStrEq("(-(*bc)a)", getFormatList(received));
			}
			test("a-b*c-d") {
				node_t *received = createEquation("a-b*c-d");
				assertStrEq("(-a(*bc)d)", getFormatList(received));
			}
			test("a*b-c*d") {
				node_t *received = createEquation("a*b-c*d");
				assertStrEq("(-(*ab)(*cd))", getFormatList(received));
			}
		}_end;
		suite("all operation") {
			formulaTest("a+b-c*d/e", "(+a(-b(*c(/de))))");
			formulaTest("a+b-c/d*e", "(+a(-b(*(/cd)e)))");

			formulaTest("a+b*c-d/e", "(+a(-(*bc)(/de)))");
			formulaTest("a+b*c/d-e", "(+a(-(*b(/cd))e))");

			formulaTest("a+b/c-d*e", "(+a(-(/bc)(*de)))");
			formulaTest("a+b/c*d-e", "(+a(-(*(/bc)d)e))");

			formulaTest("a-b+c*d/e", "(+(-ab)(*c(/de)))");
			formulaTest("a-b+c/d*e", "(+(-ab)(*(/cd)e))");

			formulaTest("a-b*c+d/e", "(+(-a(*bc))(/de))");
			formulaTest("a-b*c/d+e", "(+(-a(*b(/cd)))e)");

			formulaTest("a-b/c+d*e", "(+(-a(/bc))(*de))");
			formulaTest("a-b/c*d+e", "(+(-a(*(/bc)d))e)");

			formulaTest("a*b+c-d/e", "(+(*ab)(-c(/de)))");
			formulaTest("a*b+c/d-e", "(+(*ab)(-(/cd)e))");

			formulaTest("a*b-c+d/e", "(+(-(*ab)c)(/de))");
			formulaTest("a*b-c/d+e", "(+(-(*ab)(/cd))e)");

			formulaTest("a*b/c+d-e", "(+(*a(/bc))(-de))");
			formulaTest("a*b/c-d+e", "(+(-(*a(/bc))d)e)");

			formulaTest("a/b+c-d*e", "(+(/ab)(-c(*de)))");
			formulaTest("a/b+c*d-e", "(+(/ab)(-(*cd)e))");

			formulaTest("a/b-c+d*e", "(+(-(/ab)c)(*de))");
			formulaTest("a/b-c*d+e", "(+(-(/ab)(*cd))e)");

			formulaTest("a/b*c+d-e", "(+(*(/ab)c)(-de))");
			formulaTest("a/b*c-d+e", "(+(-(*(/ab)c)d)e)");


			/*
			test("f*b+g*r-s+a/g-s-n*f*s/g*s/r") {
				node_t *received = createEquation("f*b+g*r-s+a/g-s-n*f*s/g*s/r");
				assertStrEq("(+(*fb)(-(*gr)s)(-(/ag)s(*nf(/sg)(/sr))))", getFormatList(received));
			}
			test("f*b+g*r-s+a/g-s") {
				node_t *received = createEquation("f*b+g*r-s+a/g-s");
				assertStrEq("(+(*fb)(-(*gr)s)(-(/ag)s))", getFormatList(received));
			}
			test("a+b-c*d/r*n/f") {
				node_t *received = createEquation("a+b-c*d/r*n/f");
				assertStrEq("(+a(-b(*c(/dr)(/nf))))", getFormatList(received));
			}
			test("a+b*c-d") {
				node_t *received = createEquation("a+b*c-d");
				assertStrEq("(+a(-(*bc)d))", getFormatList(received));
			}
			*/
		}_end;
	}_end;
}_end;

_endSection_
