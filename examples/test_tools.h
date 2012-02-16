/*
 * test_tools.h
 *
 *  Created on: 14/02/2012
 *      Author: fviale
 */

#ifndef TEST_TOOLS_H_
#define TEST_TOOLS_H_

	#define TEST_TOOLS_ADD_SUITE(suite) CU_SuiteInfo suites[0];	\
										int suite_index;\
										__attribute__ ((constructor)) void build_##suite(void){ \
											suites[suite_index++] = suite; \
										}


#endif /* TEST_TOOLS_H_ */
