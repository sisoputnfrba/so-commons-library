/*
 * Copyright (C) 2019 Sistemas Operativos - UTN FRBA. All rights reserved.
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
#include <commons/collections/vector.h>
#include <commons/string.h>
#include <cspecs/cspec.h>

typedef struct
{
    char* name;
    unsigned char age;
} t_person;

static t_person person_create(char const* name, unsigned char age)
{
    return (t_person)
    {
        .name = string_duplicate((char*) name),
        .age = age
    };
}

static void person_destroy(t_person* self)
{
    free(self->name);
}

context (test_vector)
{
    void assert_person(t_person const* person, char const* name, unsigned char age)
    {
        should_ptr((void*) person) not be null;
        should_string(person->name) be equal to((char*) name);
        should_int(person->age) be equal to(age);
    }

    inline void assert_person_at_position(vector const* vector, size_t pos, char const* name, unsigned char age)
    {
        assert_person(vector_at(vector, pos), name, age);
    }

    describe ("Vector")
    {
        vector vec;
        t_person temp;

        before
        {
            vector_construct(&vec, sizeof(t_person), (VectorFreeFn) person_destroy, 0);
        } end

        after
        {
            vector_destruct(&vec);
        } end

        describe("Insertions")
        {
            it ("should insert a value at back")
            {
                temp = person_create("Matias", 24);
                vector_push_back(&vec, &temp);
                assert_person(vector_back(&vec), "Matias", 24);

                temp = person_create("Gaston", 25);
                vector_push_back(&vec, &temp);
                assert_person(vector_back(&vec), "Gaston", 25);

                should_int(vector_size(&vec)) be equal to(2);
            } end

            it ("should insert a value at position")
            {
                temp = person_create("Matias", 24);
                vector_push_back(&vec, &temp);

                temp = person_create("Sebastian", 21);
                vector_insert(&vec, 0, &temp);
                assert_person_at_position(&vec, 0, "Sebastian", 21);
                assert_person_at_position(&vec, 1, "Matias", 24);
                should_int(vector_size(&vec)) be equal to(2);

                temp = person_create("Gaston", 25);
                vector_insert(&vec, 0, &temp);
                assert_person_at_position(&vec, 0, "Gaston", 25);
                assert_person_at_position(&vec, 1, "Sebastian", 21);
                assert_person_at_position(&vec, 2, "Matias", 24);
            } end

            it("should add all elements from array at end")
            {
                t_person others[2];

                temp = person_create("Matias", 24);
                vector_push_back(&vec, &temp);

                temp = person_create("Gaston", 25);
                vector_push_back(&vec, &temp);

                temp = person_create("Sebastian", 21);
                vector_push_back(&vec, &temp);

                others[0] = person_create("Daniela", 19);
                others[1] = person_create("Facundo", 25);

                should_int(vector_size(&vec)) be equal to(3);
                vector_insert_range(&vec, vector_size(&vec), others, others + 2);
                should_int(vector_size(&vec)) be equal to(5);

                assert_person_at_position(&vec, 0, "Matias"   , 24);
                assert_person_at_position(&vec, 1, "Gaston"   , 25);
                assert_person_at_position(&vec, 2, "Sebastian", 21);
                assert_person_at_position(&vec, 3, "Daniela"  , 19);
                assert_person_at_position(&vec, 4, "Facundo"  , 25);
            } end
        } end

        describe ("Replace, remove and destroy")
        {
            before
            {
                temp = person_create("Matias"   , 24);
                vector_push_back(&vec, &temp);

                temp = person_create("Gaston"   , 25);
                vector_push_back(&vec, &temp);

                temp = person_create("Sebastian", 21);
                vector_push_back(&vec, &temp);

                temp = person_create("Ezequiel" , 25);
                vector_push_back(&vec, &temp);

                temp = person_create("Facundo"  , 25);
                vector_push_back(&vec, &temp);
            } end

            it("should replace a value at index with other value")
            {
                t_person daniela = person_create("Daniela", 19);
                {
                    t_person* old = vector_at(&vec, 3);
                    assert_person(old, "Ezequiel", 25);
                    vector_erase(&vec, 3);
                }
                vector_insert(&vec, 3, &daniela);

                assert_person_at_position(&vec, 0, "Matias"   , 24);
                assert_person_at_position(&vec, 1, "Gaston"   , 25);
                assert_person_at_position(&vec, 2, "Sebastian", 21);
                assert_person_at_position(&vec, 3, "Daniela"  , 19);
                assert_person_at_position(&vec, 4, "Facundo"  , 25);
            } end

            it("should remove and destroy a value at index")
            {
                should_int(vector_size(&vec)) be equal to(5);

                {
                    t_person* aux = vector_front(&vec);
                    assert_person(aux, "Matias", 24);
                    vector_erase(&vec, 0);
                }

                assert_person_at_position(&vec, 0, "Gaston", 25);
                should_int(vector_size(&vec)) be equal to(4);
            } end

            it ("should remove and destroy a range of indices")
            {
                should_int(vector_size(&vec)) be equal to (5);

                vector_erase_range(&vec, 1, 3);

                should_int(vector_size(&vec)) be equal to (3);
                assert_person_at_position(&vec, 0, "Matias"  , 24);
                assert_person_at_position(&vec, 1, "Ezequiel", 25);
                assert_person_at_position(&vec, 2, "Facundo" , 25);
            } end

            it ("should remove last element")
            {
                should_int(vector_size(&vec)) be equal to(5);
                t_person* aux = vector_back(&vec);
                assert_person(aux, "Facundo", 25);

                vector_pop_back(&vec);
                aux = vector_back(&vec);

                assert_person(aux, "Ezequiel", 25);
                should_int(vector_size(&vec)) be equal to (4);
            } end

            it("should remove the first value that satisfies a condition")
            {
                should_int(vector_size(&vec)) be equal to(5);

                t_person const* ps = vector_data(&vec);
                for (size_t i = 0; i < vector_size(&vec); ++i)
                {
                    if (string_equals_ignore_case(ps[i].name, "Gaston"))
                    {
                        vector_erase(&vec, i);
                        break;
                    }
                }

                should_int(vector_size(&vec)) be equal to(4);
            } end

            it("should clean a vector and leave it empty")
            {
                should_int(vector_size(&vec)) be equal to(5);
                vector_clear(&vec);
                should_bool(vector_empty(&vec)) be truthy;
            } end
        } end

        describe ("Higher order functions")
        {
            before
            {
                temp = person_create("Matias"   , 24);
                vector_push_back(&vec, &temp);

                temp = person_create("Gaston"   , 25);
                vector_push_back(&vec, &temp);

                temp = person_create("Sebastian", 21);
                vector_push_back(&vec, &temp);

                temp = person_create("Ezequiel" , 25);
                vector_push_back(&vec, &temp);

                temp = person_create("Facundo"  , 25);
                vector_push_back(&vec, &temp);
            } end

            it("should filter a vector with the values that satisfies a condition")
            {
                should_int(vector_size(&vec)) be equal to(5);

                vector young_people;
                vector_construct(&young_people, sizeof(t_person), NULL, 0);
                void _addYoungPeople(t_person const* person)
                {
                    if (person->age <= 24)
                        vector_push_back(&young_people, person);
                }
                vector_iterate(&vec, (VectorClosureFn) _addYoungPeople);

                should_int(vector_size(&young_people)) be equal to(2);
                assert_person_at_position(&young_people, 0, "Matias", 24);
                assert_person_at_position(&young_people, 1, "Sebastian", 21);
                vector_destruct(&young_people);
            } end

            it("should map a vector with the function result")
            {
                char const* names_array[] = { "Matias", "Gaston", "Sebastian", "Ezequiel", "Facundo" };

                vector names;
                vector_construct(&names, sizeof(char*), NULL, 0);
                void _getNames(t_person const* person)
                {
                    vector_push_back(&names, &person->name);
                }

                vector_iterate(&vec, (VectorClosureFn) _getNames);
                for (size_t i = 0; i < 5; ++i)
                    should_string(*(char**) vector_at(&names, i)) be equal to((char*) names_array[i]);

                vector_destruct(&names);
            } end

        } end

        describe ("Swap")
        {
            before
            {
               temp = person_create("Matias"   , 24);
               vector_push_back(&vec, &temp);

               temp = person_create("Gaston"   , 25);
               vector_push_back(&vec, &temp);

               temp = person_create("Sebastian", 21);
               vector_push_back(&vec, &temp);

               temp = person_create("Ezequiel" , 25);
               vector_push_back(&vec, &temp);

               temp = person_create("Facundo"  , 25);
               vector_push_back(&vec, &temp);
            } end

            it("should exchange contents with another vector")
            {
                vector other;
                vector_construct(&other, sizeof(t_person), (VectorFreeFn) person_destroy, 0);

                temp = person_create("Lucas", 31);
                vector_push_back(&other, &temp);

                temp = person_create("Pablo", 19);
                vector_push_back(&other, &temp);

                should_int(vector_size(&other)) be equal to (2);

                vector_swap(&vec, &other);

                should_int(vector_size(&other)) be equal to (5);
                assert_person_at_position(&other, 0, "Matias"   , 24);
                assert_person_at_position(&other, 1, "Gaston"   , 25);
                assert_person_at_position(&other, 2, "Sebastian", 21);
                assert_person_at_position(&other, 3, "Ezequiel", 25);
                assert_person_at_position(&other, 4, "Facundo", 25);

                vector_destruct(&other);
            } end
        } end

        describe ("Iterator")
        {

            it("should iterate all vector values")
            {
                temp = person_create("Matias"   , 24);
                vector_push_back(&vec, &temp);
                temp = person_create("Gaston"   , 25);
                vector_push_back(&vec, &temp);
                temp = person_create("Sebastian", 21);
                vector_push_back(&vec, &temp);
                temp = person_create("Daniela"  , 19);
                vector_push_back(&vec, &temp);

                char* const names_array[] = { "Matias", "Gaston", "Sebastian", "Daniela" };
                int index = 0;

                void _list_elements(void* p)
                {
                    t_person* person = p;

                    should_ptr(person) not be null;
                    should_string(person->name) be equal to(names_array[index++]);
                }

                vector_iterate(&vec, _list_elements);
                should_int(index) be equal to(4);
            } end

        } end
    } end
}
