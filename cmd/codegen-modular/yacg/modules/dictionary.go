// Copyright 2026 GameUp Online, Inc.
// All rights reserved.
//
// NOTICE: All information contained herein is, and remains the property of GameUp
// Online, Inc. and its suppliers, if any. The intellectual and technical concepts
// contained herein are proprietary to GameUp Online, Inc. and its suppliers and may
// be covered by U.S. and Foreign Patents, patents in process, and are protected by
// trade secret or copyright law. Dissemination of this information or reproduction of
// this material is strictly forbidden unless prior written permission is obtained
// from GameUp Online, Inc.

package modules

import (
	"bufio"
	"fmt"
	"os"
	"strings"

	"github.com/emicklei/proto"
)

type Dictionary struct {
	Entries map[string]DictionaryEntry
}

type DictionaryEntry struct {
	Mappings map[string]string
}

func LoadDictionary(path string) (Dictionary, error) {
	file, err := os.Open(path)
	if err != nil {
		return Dictionary{}, err
	}
	defer file.Close()

	dictionary := make(map[string]DictionaryEntry)
	scanner := bufio.NewScanner(file)

	var currentEntry DictionaryEntry
	var currentKeys []string

	for scanner.Scan() {
		// Go line by line.
		line := strings.TrimSpace(scanner.Text())

		// Ignore empty lines and comments
		if line == "" || strings.HasPrefix(line, "#") {
			continue
		}

		// New Section: [ "type1", "type2" ]
		if strings.HasPrefix(line, "[") && strings.HasSuffix(line, "]") {
			// Save previous rule to all its keys
			for _, k := range currentKeys {
				dictionary[strings.ToLower(k)] = currentEntry
			}

			// Start new rule
			rawKeys := strings.Trim(line, "[]")
			currentKeys = strings.Split(rawKeys, ",")
			for i := range currentKeys {
				currentKeys[i] = strings.Trim(currentKeys[i], "\" ")
			}
			currentEntry = DictionaryEntry{Mappings: make(map[string]string)}
			continue
		}

		// Key/Value pair: type = "TypeRepresentation"
		parts := strings.SplitN(line, "=", 2)
		if len(parts) == 2 {
			key := strings.Trim(parts[0], "\" ")
			val := strings.Trim(parts[1], "\" ")
			currentEntry.Mappings[strings.ToLower(key)] = val
		}
	}

	// Catch the last one
	for _, k := range currentKeys {
		dictionary[k] = currentEntry
	}

	return Dictionary{Entries: dictionary}, scanner.Err()
}

func (dict Dictionary) ResolveField(field *proto.Field, context string) (string, error) {
	mapping, ok := dict.Entries[field.Type]
	if !ok {
		return "", fmt.Errorf("failed to resolve field %s: missing dictionary entry", field.Name)
	}
	return mapping.Mappings[context], nil
}
