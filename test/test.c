/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:03:47 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/17 13:04:21 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h" // Assurez-vous que ce fichier contient le prototype de get_next_line

void test_file(const char *filename)
{
    int fd;
    char *line;
    int line_count = 0;

    printf("Testing file: %s\n", filename);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", ++line_count, line);
        free(line);
    }

    printf("Total lines read: %d\n\n", line_count);
    close(fd);
}

int main(void)
{
    // Test avec un fichier normal
    test_file("test_normal.txt");

    // Test avec un fichier vide
    test_file("test_empty.txt");

    // Test avec un fichier d'une seule ligne sans retour à la ligne
    test_file("test_one_line_no_nl.txt");

    // Test avec un fichier d'une seule ligne avec retour à la ligne
    test_file("test_one_line_with_nl.txt");

    // Test avec un fichier contenant seulement des retours à la ligne
    test_file("test_only_newlines.txt");

    // Test avec un descripteur de fichier invalide
    printf("Testing with invalid file descriptor:\n");
    char *line = get_next_line(-1);
    if (line == NULL)
        printf("Correctly returned NULL for invalid fd\n\n");
    else
    {
        printf("Error: did not return NULL for invalid fd\n\n");
        free(line);
    }

    return 0;
}
