#include "shell.h"

/**
 * _memcpy - copies information between void pointers.
 * @newptr: this is the pointer that shows the destination.
 * @ptr: this is the main/source pointer.
 * @size: size of the pointer.
 *
 * Return: null.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - shifts and allocates the memory block.
 * @ptr: pointer of the memory allocated.
 * @old_size: size of the pointer.
 * @new_size: new sizeof the latest mem block.
 *
 * Return: ptr.
 * if new_size == old_size, returns the pointer with zero changes.
 * if malloc does not work, returns a value of NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - allocates a nd shifts to a double pointer.
 * @ptr: this is the double pointer to the memory reallocated.
 * @old_size: size of the pointer allocated.
 * @new_size: this is the enw size of the current pointer/memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns the pointer with zero changes.
 * if malloc does not, returns a value of NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
