/*
 * C128 CP/M sentence generator.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <vic.h>
#include "demo.h"
/*
 * Generate random sentence about birds.
 */
char* generateSentence() {
	static char *articles[] = { "The", "A" };
	static char *nouns[] = { "blue jay", "cardinal", "eastern phoebe", "grackle", "sandhill crane" };
	static char *verbs[] = { "flies", "jumps", "sleeps", "eats", "walks" };
	static char *adjectives[] = { "big", "small", "angry", "wet", "happy" };
	char *sentence = malloc(100);
	int articleIndex = rand() % (sizeof(articles) / sizeof(articles[0]));
	int nounIndex = rand() % (sizeof(nouns) / sizeof(nouns[0]));
	int verbIndex = rand() % (sizeof(verbs) / sizeof(verbs[0]));
	int adjectiveIndex = rand() % (sizeof(adjectives) / sizeof(adjectives[0]));
	sentence[0] = '\0';
	sprintf(sentence, "%s %s %s %s.", articles[articleIndex], adjectives[adjectiveIndex], nouns[nounIndex], verbs[verbIndex]);
	return sentence;
}
