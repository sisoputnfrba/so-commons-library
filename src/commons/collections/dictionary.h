
#ifndef DICTIONARY_H_
#define DICTIONARY_H_

	#define DEFAULT_DICTIONARY_SIZE 50

	typedef struct {
		t_hash_element *elements;
		void (*data_destroyer)(void*);
		int maxsize;
		int size;
	} t_dictionary;

	t_dictionary *dictionary_create(void(*data_destroyer)(void*));
	int 		  dictionary_put(t_dictionary *, char *key, void *data);
	void 		 *dictionary_get(t_dictionary *, char *key);
	void 		 *dictionary_remove(t_dictionary *, char *key);
	void 		  dictionary_remove_and_destroy(t_dictionary *, char *key);
	void 		  dictionary_iterator(t_dictionary *, void(*closure)(void*));
	void 		  dictionary_clean(t_dictionary *);
	int 		  dictionary_is_empty(t_dictionary *);
	int 		  dictionary_size(t_dictionary *);
	void 		  dictionary_destroyer(t_dictionary *);

#endif /* DICTIONARY_H_ */

