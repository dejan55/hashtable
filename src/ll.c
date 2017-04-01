/*
 * This file is part of Hashtable.
 * Hashtable is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hashtable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hashtable.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <string.h>
#include "ll.h"

void ll_add(ll **list, char *key, char *value) {
	ll *tmp = *list;
	*list = (ll *)malloc(sizeof(ll));
	(*list)->next = tmp;
	(*list)->key = strdup(key);
	(*list)->value = strdup(value);

	return;
}

void ll_remove(ll **list, char *key) {
	ll *tmp, *prev = NULL, *next;

	if (list == NULL) {
		return;
	}

	tmp = *list;

	while (tmp) {
		if (!strcmp(tmp->key, key)) {
			free(tmp->key);
			free(tmp->value);

			next = tmp->next;

			free(tmp);

			if (prev != NULL) {
				prev->next = next;
			} else {
				*list = next;
			}

			return;
		}

		prev = tmp;
		tmp = tmp->next;
	}

	return;
}

ll *ll_find(ll *list, char *key) {
	ll_iterator iterator;
	ll *tmp;

	for (iterator = ll_iterator_start(list); !ll_iterator_end(&iterator); ll_iterator_next(&iterator)) {
		tmp = ll_iterator_get(&iterator);

		if (!strcmp(ll_get_key(tmp), key)) {
			return tmp;
		}
	}

	return NULL;
}

void ll_free(ll *list) {
	ll *tmp;

	while (list) {
		tmp = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = tmp;
	}

	return;
}

char *ll_get_key(ll *list) {
	return list == NULL ? NULL : list->key;
}

char *ll_get_value(ll *list) {
	return list == NULL ? NULL : list->value;
}

void ll_set_key(ll *list, char *key) {
	if (list == NULL) {
		return;
	}

	free(list->key);
	list->key = strdup(key);
}

void ll_set_value(ll *list, char *value) {
	if (list == NULL) {
		return;
	}

	free(list->value);
	list->value = strdup(value);
}

ll_iterator ll_iterator_start(ll *list) {
	ll_iterator iterator;

	iterator.head = iterator.current = list;
	return iterator;
}

ll *ll_iterator_get(ll_iterator *iterator) {
	return iterator->current;
}

int ll_iterator_end(ll_iterator *iterator) {
	return iterator->current == NULL;
}

void ll_iterator_next(ll_iterator *iterator) {
	if (ll_iterator_end(iterator)) {
		return;
	}

	iterator->current = iterator->current->next;
}
