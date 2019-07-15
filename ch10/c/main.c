#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "hashmap.h"

void test_hashmap_new(void);
void test_hashmap_setget(void);
void test_hashmap_del(void);
void test_hashmap_resize(void);
void test_hashmap_hash(void);

int main(void)
{
    test_hashmap_hash();
    test_hashmap_new();
    test_hashmap_setget();
    test_hashmap_del();
    test_hashmap_resize();
}

void test_hashmap_hash(void)
{
    printf("Testing hashmap hash...");
    HashMap *hm = hashmap_new(5, 0);

    int hk0 = hashmap_hash(hm, 0);
    int hk1 = hashmap_hash(hm, 1);
    int hk2 = hashmap_hash(hm, 2);
    int hk3 = hashmap_hash(hm, 3);
    int hk4 = hashmap_hash(hm, 4);

    printf("%i\n", hk0);
    printf("%i\n", hk1);
    printf("%i\n", hk2);
    printf("%i\n", hk3);
    printf("%i\n", hk4);
    printf("OK!\n");

}
void test_hashmap_new(void)
{
    printf("Testing hashmap new...");
    HashMap *hm = hashmap_new(11, 0);

    assert (hm->tbl_capacity == 11);
    assert (hm->n == 0);
    assert (hm->p == 109345121);
    printf("OK!\n");
}

void test_hashmap_setget(void)
{
    printf("Testing hashmap set...");
    HashMap *hm = hashmap_new(5, 0);

    hashmap_set(hm, 1, 3);

    printf("%i: (%i, %i)\n", 0, hm->table[0]->key, hm->table[0]->value);
    printf("%i: (%i, %i)\n", 1, hm->table[1]->key,hm->table[1]->value);
    printf("%i: (%i, %i)\n", 2, hm->table[2]->key,hm->table[2]->value);
    printf("%i: (%i, %i)\n", 3, hm->table[3]->key,hm->table[3]->value);
    printf("%i: (%i, %i)\n", 4, hm->table[4]->key,hm->table[4]->value);

    hashmap_set(hm, 2, 4);
    printf("Adding hash...\n");

    printf("%i: (%i, %i)\n", 0, hm->table[0]->key,hm->table[0]->value);
    printf("%i: (%i, %i)\n", 1, hm->table[1]->key,hm->table[1]->value);
    printf("%i: (%i, %i)\n", 2, hm->table[2]->key,hm->table[2]->value);
    printf("%i: (%i, %i)\n", 3, hm->table[3]->key,hm->table[3]->value);
    printf("%i: (%i, %i)\n", 4, hm->table[4]->key,hm->table[4]->value);

    hashmap_set(hm, 3, 5);
    printf("Adding hash...\n");

    printf("%i: (%i, %i)\n", 0, hm->table[0]->key,hm->table[0]->value);
    printf("%i: (%i, %i)\n", 1, hm->table[1]->key,hm->table[1]->value);
    printf("%i: (%i, %i)\n", 2, hm->table[2]->key,hm->table[2]->value);
    printf("%i: (%i, %i)\n", 3, hm->table[3]->key,hm->table[3]->value);
    printf("%i: (%i, %i)\n", 4, hm->table[4]->key,hm->table[4]->value);
    printf("%i: (%i, %i)\n", 5, hm->table[5]->key,hm->table[5]->value);
    printf("%i: (%i, %i)\n", 6, hm->table[6]->key,hm->table[6]->value);
    printf("%i: (%i, %i)\n", 7, hm->table[7]->key,hm->table[7]->value);
    printf("%i: (%i, %i)\n", 8, hm->table[8]->key,hm->table[8]->value);

    assert (hm->n == 3);
    assert (hm->tbl_capacity == 9);

    printf("OK!\n");
    printf("Testing hashmap get...");

    int val = hashmap_get(hm, 1);
    
    assert (val == 3);
    printf("OK!\n");
}

void test_hashmap_del(void)
{
    printf("Testing hashmap del...");
    HashMap *hm = hashmap_new(5, 0);

    hashmap_set(hm, 1, 3);
    hashmap_set(hm, 2, 4);

    assert (hm->n == 2);
    assert (hashmap_get(hm, 1) == 3);
    assert (hashmap_get(hm, 2) == 4);

    hashmap_del(hm, 2);

    assert (hm->n == 1);
    printf("OK!\n");
}

void test_hashmap_resize(void)
{
    printf("Testing hashmap resize...");
    HashMap *hm = hashmap_new(2, 0);
    assert (hm->tbl_capacity == 2);

    hashmap_set(hm, 1, 3);
    assert (hm->tbl_capacity == 2);

    hashmap_set(hm, 2, 4);
    assert (hm->tbl_capacity == 5);
    printf("OK!\n");
}
