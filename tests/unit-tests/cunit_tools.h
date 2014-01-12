/*
 * Copyright (C) 2012 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
