#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>

typedef struct ring_buffer ring_buffer_t ;

ring_buffer_t * rb_create(size_t capacity) ;
void rb_destroy(ring_buffer_t ** rb) ;

int rb_write(ring_buffer_t * rb , const void * data , size_t len) ;
int rb_read(ring_buffer_t *rb , void * data ,size_t len) ;

size_t rb_available(ring_buffer_t * rb) ;
size_t rb_free_space(ring_buffer_t * rb) ;

void rb_clear(ring_buffer_t * rb) ;

#endif