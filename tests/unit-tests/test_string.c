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

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <commons/string.h>

#include "cspecs/cspec.h"


context (test_string) {

    describe ("String") {

        it("itoa") {
            char* newString = string_itoa(15);
            should_string(newString) be equal to("15");
            free(newString);
        } end

        it("from_format") {
            char* newString = string_from_format("%s %s %d", "Hello", "world", 23);
            should_string(newString) be equal to("Hello world 23");
            free(newString);
        } end

        it("append") {
            char *string = string_new();
            string_append(&string, "Hello");
            string_append(&string, " ");
            string_append(&string, "world");

            should_string(string) be equal to("Hello world");

            free(string);
        } end

        it("n_append") {
            char *string = string_new();
            string_n_append(&string, "Hello", 10);
            string_n_append(&string, "     ", 1);
            string_n_append(&string, "world", 5);

            should_string(string) be equal to("Hello world");

            free(string);
        } end

        it("append_with_format") {
            char *string = string_new();

            string_append_with_format(&string, "%s %s %d", "Hello", "world", 23);
            should_string(string) be equal to("Hello world 23");

            free(string);
        } end

        it("equals_ignore_case") {
            char *string = string_duplicate("Hello WorLd");

            should_bool(string_equals_ignore_case(string, "hello world")) be truthy;

            free(string);
        } end

        it("repeat") {
            char *string = string_repeat('a', 10);

            should_string(string) be equal to("aaaaaaaaaa");
            should_int(strlen(string)) be equal to(10);

            free(string);
        } end

        it("to_upper") {
            char *string = string_duplicate("Hello World");
            string_to_upper(string);

            should_string(string) be equal to("HELLO WORLD");

            free(string);
        } end

        it("to_lower") {
            char *string = string_duplicate("Hello World");
            string_to_lower(string);

            should_string(string) be equal to("hello world");

            free(string);
        } end

        it("capitalized") {
            char *string;

            string = string_duplicate("hello world");
            string_capitalized(string);
            should_string(string) be equal to("Hello world");
            free(string);

            string = string_duplicate("HELLO WORLD");
            string_capitalized(string);
            should_string(string) be equal to("Hello world");
            free(string);

            string = string_duplicate("hi");
            string_capitalized(string);
            should_string(string) be equal to("Hi");
            free(string);

            string = string_duplicate("h");
            string_capitalized(string);
            should_string(string) be equal to("H");
            free(string);
        } end

        describe("Trim") {

                it("trim_left") {
                    char *string;

                    string = string_duplicate("Hola");
                    string_trim_left(&string);
                    should_string(string) be equal to("Hola");
                    free(string);

                    string = string_duplicate("   Hola");
                    string_trim_left(&string);
                    should_string(string) be equal to("Hola");
                    free(string);
                } end

                it("trim_right") {
                    char *string;

                    string = string_duplicate("Hola");
                    string_trim_right(&string);
                    should_string(string) be equal to("Hola");
                    free(string);

                    string = string_duplicate("Hola    ");
                    string_trim_right(&string);
                    should_string(string) be equal to("Hola");
                    free(string);
                } end

                it("trim") {
                    char *string;

                    string = string_duplicate("Hola");
                    string_trim(&string);
                    should_string(string) be equal to("Hola");
                    free(string);

                    string = string_duplicate("    Hola");
                    string_trim(&string);
                    should_string(string) be equal to("Hola");
                    free(string);

                    string = string_duplicate("Hola    ");
                    string_trim(&string);
                    should_string(string) be equal to("Hola");
                    free(string);

                    string = string_duplicate("    Hola    ");
                    string_trim(&string);
                    should_string(string) be equal to("Hola");
                    free(string);
                } end

        } end

        it("is_empty") {
            char *string = string_new();
            should_bool(string_is_empty(string)) be truthy;
            free(string);
        } end

        describe("Split") {

            it("split_with_separator_found") {
                char *line = "path\\to\\file";
                char** substrings = string_split(line, "\\");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to ("path");
                should_string(substrings[1]) be equal to ("to");
                should_string(substrings[2]) be equal to ("file");
                should_ptr(substrings[3]) be null;

                string_array_destroy(substrings);
            } end

            it("split_with_separator_not_found") {
                char *line = "path";
                char **substrings = string_split(line, "/");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to ("path");
                should_ptr(substrings[1]) be null;

                string_array_destroy(substrings);
            } end

            it("split_with_empty_string_as_separator") {
                char *line = "hello";
                char** substrings = string_split(line, "");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to ("h");
                should_string(substrings[1]) be equal to ("e");
                should_string(substrings[2]) be equal to ("l");
                should_string(substrings[3]) be equal to ("l");
                should_string(substrings[4]) be equal to ("o");
                should_ptr(substrings[5]) be null;

                string_iterate_lines(substrings, (void*) free);
                free(substrings);
            } end

            it("split_with_null_separator") {
                char *line = "path/to/file";
                char** substrings = string_split(line, NULL);

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to ("path/to/file");
                should_ptr(substrings[1]) be null;

                string_iterate_lines(substrings, (void*) free);
                free(substrings);
            } end

            it("split_starting_with_separator") {
                char* line = "/path/to/file";
                char** substrings = string_split(line, "/");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to ("");
                should_string(substrings[1]) be equal to ("path");
                should_string(substrings[2]) be equal to ("to");
                should_string(substrings[3]) be equal to ("file");
                should_ptr(substrings[4]) be null;

                string_array_destroy(substrings);
            } end

            it("split_ending_with_separator") {
                char* line = "path/to/file/";
                char** substrings = string_split(line, "/");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to ("path");
                should_string(substrings[1]) be equal to ("to");
                should_string(substrings[2]) be equal to ("file");
                should_string(substrings[3]) be equal to ("");
                should_ptr(substrings[4]) be null;

                string_array_destroy(substrings);
            } end

            it("split_having_separators_in_between") {
                char* line = "path/to//file";
                char** substrings = string_split(line, "/");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to ("path");
                should_string(substrings[1]) be equal to ("to");
                should_string(substrings[2]) be equal to ("");
                should_string(substrings[3]) be equal to ("file");
                should_ptr(substrings[4]) be null;

                string_array_destroy(substrings);
            } end

            it("split_is_empty") {
                char* line = "";
                char** substrings = string_split(line, "/");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to("");
                should_ptr(substrings[1]) be null;

                string_array_destroy(substrings);

            } end

            it("split_is_empty_with_empty_separator") {
                char* line = "";
                char** substrings = string_split(line, "");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to("");
                should_ptr(substrings[1]) be null;

                string_array_destroy(substrings);

            } end

            it("n_split_when_n_is_less_than_splitted_elements") {
                char *line = "Hola planeta tierra";
                char** substrings = string_n_split(line, 2, " ");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to("Hola");
                should_string(substrings[1]) be equal to("planeta tierra");
                should_ptr(substrings[2]) be null;

                string_array_destroy(substrings);
            } end

            it("n_split_when_n_is_equals_than_splitted_elements") {
                char *line = "Hola planeta tierra";
                char** substrings = string_n_split(line, 3, " ");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to("Hola");
                should_string(substrings[1]) be equal to("planeta");
                should_string(substrings[2]) be equal to("tierra");
                should_ptr(substrings[3]) be null;

                string_array_destroy(substrings);
            } end

            it("n_split_when_separator_isnt_included") {
                char *line = "Hola planeta tierra";
                char ** substrings = string_n_split(line, 5, ";");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to(line);
                should_ptr(substrings[1]) be null;

                string_array_destroy(substrings);
            } end

            it("n_split_when_n_is_greather_than_splitted_elements") {
                char *line = "Hola planeta tierra";
                char** substrings = string_n_split(line, 10, " ");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to("Hola");
                should_string(substrings[1]) be equal to("planeta");
                should_string(substrings[2]) be equal to("tierra");
                should_ptr(substrings[3]) be null;

                string_array_destroy(substrings);
            } end

            it("n_split_is_empty") {
                char* line = "";
                char** substrings = string_n_split(line, 10, ";");

                should_ptr(substrings) not be null;
                should_string(substrings[0]) be equal to("");

                string_array_destroy(substrings);
            } end

        } end

        it("starts_with") {
            should_bool(string_starts_with("#Comentario", "#")) be truthy;
            should_bool(string_starts_with("Comentario", "Comen")) be truthy;
            should_bool(string_starts_with("Comentario", "comen")) be falsey;
            should_bool(string_starts_with("Comentario", "lala")) be falsey;
            should_bool(string_starts_with("", "#")) be falsey;
        } end

        it("ends_with") {
            should_bool(string_ends_with("MiArchivo.txt", "txt")) be truthy;
            should_bool(string_ends_with("MiArchivo.txt", "MiArchivo.txt")) be truthy;
            should_bool(string_ends_with("MiArchivo.doc", "txt")) be falsey;
            should_bool(string_ends_with("MiDoc", "txt")) be falsey;
            should_bool(string_ends_with("", "txt")) be falsey;
        } end

        describe("Substring") {

                it("substring_empty") {
                    char* original_word = "";
                    char* substring = string_substring(original_word, 0, 3);
                    should_string(substring) be equal to(original_word);
                    should_ptr(substring) not be equal to(original_word);
                    free(substring);
                } end

                it("substring_with_short_string") {
                    char* original_word = "hola";
                    char* substring = string_substring(original_word, 0, 14);
                    should_string(substring) be equal to(original_word);
                    should_ptr(substring) not be equal to(original_word);
                    free(substring);
                } end

                it("substring_with_large_string") {
                    char* original_word = "hola mundo c!";
                    char* substring = string_substring(original_word, 0, 4);
                    should_string(substring) be equal to("hola");
                    should_ptr(substring) not be equal to(original_word);
                    free(substring);
                } end

                it("substring_from_other_start") {
                    char* original_word = "hola mundo!";
                    char* substring = string_substring(original_word, 5, strlen(original_word) - 5);
                    should_string(substring) be equal to("mundo!");
                    should_ptr(substring) not be equal to(original_word);
                    free(substring);
                } end

                it("substring_extract_internal_text") {
                    char* original_word = "hola mundo";
                    char* substring = string_substring(original_word, 2, 5);
                    should_string(substring) be equal to("la mu");
                    should_ptr(substring) not be equal to(original_word);
                    free(substring);
                } end

                it("substring_with_equal_large") {
                    char* original_word = "hola";
                    char* substring = string_substring(original_word, 0, 4);
                    should_string(substring) be equal to(original_word);
                    should_ptr(substring) not be equal to(original_word);
                    free(substring);
                } end

                it("substring_from_middle") {
                    char *original = "hola mundo!";
                    char *substring = string_substring_from(original, 5);
                    should_string(substring) be equal to("mundo!");
                    should_ptr(substring) not be equal to(original);
                    free(substring);
                } end

                it("substring_from_start") {
                    char *original = "hola mundo!";
                    char *substring = string_substring_from(original, 0);
                    should_string(substring) be equal to(original);
                    should_ptr(substring) not be equal to(original);
                    free(substring);
                } end

                it("substring_until_middle") {
                    char *original = "hola mundo!";
                    char *substring = string_substring_until(original, 5);
                    should_string(substring) be equal to("hola ");
                    should_ptr(substring) not be equal to(original);
                    free(substring);
                } end

                it("substring_until_end") {
                    char *original = "hola mundo!";
                    char *substring = string_substring_until(original, strlen(original));
                    should_string(substring) be equal to(original);
                    should_ptr(substring) not be equal to(original);
                    free(substring);
                } end

        } end

        describe("String as array") {

                it("get_string_as_array_empty") {
                    char* string_empty_array = "[]";
                    char** empty_array = string_get_string_as_array(string_empty_array);
                    should_ptr(empty_array) not be null;
                    should_ptr(empty_array[0]) be null;

                    string_array_destroy(empty_array);
                } end

                it("get_string_full_array") {
                    char* numbers = "[1, 2, 3, 4, 5]";
                    char** numbers_array = string_get_string_as_array(numbers);
                    should_ptr(numbers_array) not be null;
                    should_ptr(numbers_array[5]) be null;

                    int i;
                    for (i = 1; i <= 5; ++i) {
                        char* value = string_from_format("%d", i);
                        should_string(numbers_array[i - 1]) be equal to(value);
                        free(value);
                    }

                    string_array_destroy(numbers_array);

                } end

        } end

        it("length") {
            should_int(string_length("hola")) be equal to(4);
        } end

        describe("Reverse") {

            it ("reverse with length of a string is even") {
                char* word = "CASA";
                char* reverse_word = string_reverse(word);
                should_string(reverse_word) be equal to("ASAC");
                free(reverse_word);
            } end

            it ("reverse with length of a string is odd") {
                char* word = "FRUTA";
                char* reverse_word = string_reverse(word);
                should_string(reverse_word) be equal to("ATURF");
                free(reverse_word);
            } end

            it ("reverse with empty string") {
                char* word = "";
                char* reverse_word = string_reverse(word);
                should_string(reverse_word) be equal to("");
                free(reverse_word);
            } end
        } end

        describe("Replacing") {
            char* replaced;

            after {
                free(replaced);
            } end

            it ("replace multiple occurrences") {
                replaced = string_replace("hexxo worxd!", "x", "l");
                should_string(replaced) be equal to ("hello world!");
            } end

            it ("replace an occurrence with a longer one") {
                replaced = string_replace("hello", "o", "o world!");
                should_string(replaced) be equal to ("hello world!");
            } end

            it ("replace an occurrence with a shorter one") {
                replaced = string_replace("hello", "ello", "ola");
                should_string(replaced) be equal to ("hola");
            } end

            it ("replace every occurrence with empty string") {
                replaced = string_replace("hello", "l", "");
                should_string(replaced) be equal to ("heo");
            } end

            it ("replace duplicates original when doesn't receive a substring as pattern") {
                replaced = string_replace("hello", "definitely not a substring", "test failed!");
                should_string(replaced) be equal to ("hello");
            } end
        } end

        it("Contains") {
          should_bool(string_contains("Pablito clavo un clavito", "Pablito")) be truthy;
          should_bool(string_contains("Pablito clavo un clavito", "pablito")) be falsey;
          should_bool(string_contains("Pablito clavo un clavito", "lito")) be truthy;
          should_bool(string_contains("Pablito clavo un clavito", "")) be truthy;
          should_bool(string_contains("", "Pablito clavo un clavito")) be falsey;
          should_bool(string_contains("", "")) be truthy;
        } end

        describe ("String array") {
            char** names;

            before {
                names = string_array_new();

                string_array_push(&names, "Gaston");
                string_array_push(&names, "Matias");
                string_array_push(&names, "Sebastian");
                string_array_push(&names, "Daniela");
            } end

            after {
                free(names);
            } end

            it ("add an element at the end") {
                string_array_push(&names, "Agustin");

                should_int(string_array_size(names)) be equal to (5);
                should_ptr(names[5]) be null;

                char* expected[] = {"Gaston", "Matias", "Sebastian", "Daniela", "Agustin"};
                int i = 0;
                void _assert_names(char* name) {
                    should_ptr(name) not be null;
                    should_string(name) be equal to (expected[i]);
                    i++;
                }
                string_iterate_lines(names, _assert_names);
            } end

            it("remove the last element") {
                char* name = string_array_pop(names);

                should_string(name) be equal to ("Daniela");

                should_int(string_array_size(names)) be equal to (3);
                should_ptr(names[3]) be null;

                char* expected[] = {"Gaston", "Matias", "Sebastian"};
                int i = 0;
                void _assert_names(char* name) {
                    should_ptr(name) not be null;
                    should_string(name) be equal to (expected[i]);
                    i++;
                }
                string_iterate_lines(names, _assert_names);
            } end

            it("replace an element") {
                char* name = string_array_replace(names, 2, "Damian");

                should_string(name) be equal to ("Sebastian");

                char* expected[] = {"Gaston", "Matias", "Damian", "Daniela"};
                int i = 0;
                void _assert_names(char* name) {
                    should_ptr(name) not be null;
                    should_string(name) be equal to (expected[i]);
                    i++;
                }
                string_iterate_lines(names, _assert_names);
            } end
        } end
    } end
}
