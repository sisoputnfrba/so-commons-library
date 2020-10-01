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

#include "txt.h"

#include <stdlib.h>
#include <commons/string.h>
#include <readline/readline.h>
#include <readline/history.h>

char** _get_tokens_array(char* line, int* argc);

FILE* txt_open_for_append(char* path) {
	return fopen(path, "a");
}

void txt_write_in_file(FILE* file, char* bytes) {
	fprintf(file, "%s", bytes);
	fflush(file);
}

void txt_write_in_stdout(char* string) {
	printf("%s", string);
	fflush(stdout);
}

void txt_close_file(FILE* file) {
	fclose(file);
}

char** txt_read_line_in_stdin(const char* prompt, int* argc) {
	char *line, **argv = NULL;
	int args_count = 0;

	line = readline(prompt);
	if(line[0] != '\0') {
		add_history(line);
		argv = _get_tokens_array(line, &args_count);
	}
	free(line);

	if(argc != NULL) {
		*argc = args_count;
	}

	return argv;
}

char** _get_tokens_array(char* line, int* argc) {
	char *buff, *token, **argv = NULL;

	buff = line;
	token = strtok_r(line, " ", &buff);

	if(token != NULL) {
		(*argc)++;
		argv = realloc(argv, sizeof(char*) * (*argc));
		argv[(*argc) - 1] = strdup(token);

		while(buff[0] != '\0') {
			token = strtok_r(NULL, " ", &buff);
			if(token == NULL) {
				break;
			}
			(*argc)++;
			argv = realloc(argv, sizeof(char*) * (*argc));
			argv[(*argc) - 1] = strdup(token);
		}
	}
	argv = realloc(argv, sizeof(char*) * ((*argc) + 1));
	argv[(*argc)] = NULL;

	return argv;
}
