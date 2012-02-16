/*
 * test_tools.h
 *
 *  Created on: 14/02/2012
 *      Author: fviale
 */

#ifndef CUNIT_TOOLS_H_
#define CUNIT_TOOLS_H_


	#define CUNIT_MAKE_SUITE(name, desc, init_suite_func, clean_suite_func, tests) \
								static CU_SuiteInfo name##_suite = { desc, init_suite_func, clean_suite, tests };\
								CU_SuiteInfo suites[0];	\
								int suite_index;\
								__attribute__ ((constructor)) void build_suite_##name(void){ \
									suites[suite_index++] = name##_suite; \
								}


#endif /* CUNIT_TOOLS_H_ */
