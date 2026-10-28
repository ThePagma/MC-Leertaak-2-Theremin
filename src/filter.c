//
// Created by Deeq on 28/10/2026.
//

#include <stdint.h>
#include <stdlib.h>
#include "filter.h"

struct Sample {
    uint8_t age;      // hoe oud deze meting is
    uint16_t value;   // de gemeten afstand in cm
};

static struct Sample *samples = NULL;   // wijst naar het geheugen van het filter
static uint8_t filterSize = 0;          // hoeveel metingen er in het filter passen
static uint16_t lastValue = 0;
#define FILTER_MIN 1
#define FILTER_MAX 15

void filter_init(uint8_t size) {
    samples = calloc(size, sizeof(struct Sample));   // vraag geheugen aan

    if (samples == NULL) {
        filterSize = 0;
    } else {
        filterSize = size;
    }
}

static int compareSamples(const void *a, const void *b) {
    const struct Sample *sa = a;   // a is eigenlijk een pointer naar een Sample
    const struct Sample *sb = b;

    if (sa->value < sb->value) {
        return -1;   // sa hoort vóór sb
    }
    if (sa->value > sb->value) {
        return 1;    // sa hoort ná sb
    }
    return 0;        // ze zijn gelijk
}

static int compareAge(const void *a, const void *b) {
    const struct Sample *sa = a;   // a is eigenlijk een pointer naar een Sample
    const struct Sample *sb = b;

    if (sa->age < sb->age) {
        return -1;   // sa hoort vóór sb
    }
    if (sa->age > sb->age) {
        return 1;    // sa hoort ná sb
    }
    return 0;        // ze zijn gelijk
}

void filter_setSize(uint8_t newSize) {
    if (newSize < FILTER_MIN) {
        newSize = FILTER_MIN;
    }else if (newSize > FILTER_MAX) {
        newSize = FILTER_MAX;
    }

    if (newSize == filterSize) {
        return;   // niets te doen
    }

    if (newSize < filterSize && samples != NULL) {
        qsort(samples, filterSize, sizeof(struct Sample), compareAge);
    }

    struct Sample *newSamples = realloc(samples, newSize * sizeof(struct Sample));
    if (newSamples == NULL) {
        return;
    }
    samples = newSamples;

    // nieuwe plekken vullen (alleen bij groter maken)
    for (uint8_t i = filterSize; i < newSize; i++) {
        samples[i].value = lastValue;
        samples[i].age = 0;
    }

    filterSize = newSize;
}


static void filter_add(uint16_t value) {
    lastValue = value;
    if (samples == NULL) {
        return;   // niets om in te bewaren
    }

    // 1. alle metingen een stapje ouder maken
    for (uint8_t i = 0; i < filterSize; i++) {
        samples[i].age = samples[i].age + 1;
    }

    // 2. de oudste meting zoeken
    uint8_t oldest = 0;
    for (uint8_t i = 1; i < filterSize; i++) {
        if (samples[i].age > samples[oldest].age) {
            oldest = i;
        }
    }

    // 3. de oudste vervangen door de nieuwe meting
    samples[oldest].value = value;
    samples[oldest].age = 0;
}

uint16_t filter_apply(uint16_t value) {
    filter_add(value);

    if (samples == NULL) {
        return value;   // optie A: geen geheugen, dus de meting ongefilterd doorgeven
    }

    // sorteer op value; compareSamples zonder () = function pointer
    qsort(samples, filterSize, sizeof(struct Sample), compareSamples);

    return samples[filterSize / 2].value;   // de middelste meting is de mediaan
}