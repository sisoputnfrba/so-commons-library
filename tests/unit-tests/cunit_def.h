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

#ifndef CUNIT_DEF_H_
#define CUNIT_DEF_H_

	#include <CUnit/Basic.h>

	#ifndef DEFAULT_MAX_SUITES
		#define DEFAULT_MAX_SUITES 100
	#endif

	int suite_index = 0;

	CU_SuiteInfo suites[] = { [ 0 ... (DEFAULT_MAX_SUITES - 1)] = CU_SUITE_INFO_NULL};

#endif /* CUNIT_DEF_H_ */
