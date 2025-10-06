#include "ring_buffer_driver.h"
#include <string.h>
#include <stdlib.h>
 #include <stdio.h>

struct ring_buffer
{
    char * buffer ;
    size_t capacity ;
    size_t write ;
    size_t read ;
    size_t count ;
};

ring_buffer_t * rb_create(size_t capacity){
    ring_buffer_t * rb = malloc(sizeof(*rb)) ;
    if(!rb) {
        perror("malloc") ;
        return NULL ;
    }
    char * buffer = malloc(capacity);
    if(!buffer){
        free(rb) ;
        rb = NULL ;
        perror("malloc") ;
        return NULL ;
    }
    rb->buffer = buffer ;
    rb->capacity = capacity ;
    rb->read = 0 ;
    rb->write = 0 ;
    rb->count =  0;

    return rb ;
}

void rb_destroy(ring_buffer_t ** rb){
    if(rb){
        free((*rb)->buffer);
        (*rb)->buffer=NULL ;
        free(*rb) ;
        *rb = NULL ;
    }
    return ;
}

int rb_write(ring_buffer_t * rb , const void * data , size_t len){
    /**
     * TODO : 
     */
    return 0 ;
}

size_t rb_available(ring_buffer_t * rb){
    /**
     * TODO : 
     */
    return 0 ;
}

size_t rb_free_space(ring_buffer_t * rb){
    /**
     * TODO : 
     */
    return 0 ;
}

void rb_clear(ring_buffer_t * rb) {
    /**
     * TODO : 
     */
}