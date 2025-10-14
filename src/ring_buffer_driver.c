#include "ring_buffer_driver.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NDEBUG
#include <assert.h>

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
        // assert(rb==NULL) ;
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
    if((rb->capacity - rb->count ) >= len && len>0){
        if(len>rb->capacity-rb->write){
            memcpy(rb->buffer+rb->write,data ,rb->capacity-rb->write) ;
            memcpy(rb->buffer ,data + rb->capacity - rb->write, len-(rb->capacity-rb->write) ) ;
        }else{
            memcpy(rb->buffer+rb->write, data , len) ;}
        rb->write = (rb->write + len) % rb->capacity ;
        rb->count += len ;
        return len ;
    }
    perror("Fatal : rb_write") ;
    return -1 ;
}

int rb_read(ring_buffer_t *rb , void * data ,size_t len) {
    if( len > 0 ){
        len = (len > rb->count) ? rb->count : len;
        if((rb->capacity-rb->read )>= len ){
            memcpy (data , rb->buffer + rb->read , len);
            rb->read = (rb->read + len) % rb->capacity ;
        }else{
            memcpy (data , rb->buffer + rb->read , rb->capacity - rb->read) ;
            memcpy (data + (rb->capacity - rb->read) , rb->buffer , len - (rb->capacity -rb->read)) ;
            rb->read = len - (rb->capacity - rb->read);
        }
        rb->count -= len ;
        return len ;
    }
    perror("Fatal : rb_read") ;
    return -1 ;
}

size_t rb_available(ring_buffer_t * rb){
    
    return rb->count ;
}

size_t rb_free_space(ring_buffer_t * rb){
    return rb->capacity - rb->count;
}

void rb_clear(ring_buffer_t * rb) {
    memset(rb->buffer ,0 , rb->capacity);
    rb->read = rb->write = rb->count = 0 ;
}