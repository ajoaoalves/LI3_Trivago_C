#ifndef PARSER_H
#define PARSER_H

/**
 * @brief Função que trata do parsing de arquivos CSV.
 *
 * Esta função lê um arquivo CSV no caminho especificado e executa a função de construção (buildStruct) para processar os dados do arquivo. Os parâmetros adicionais (structure1,
 * structure2, structure3) são passados à função de construção para auxiliar no processamento.
 *
 * @param path 
 * @param buildStruct 
 * @param structure1 
 * @param structure2 
 * @param structure3 
 */
void parser(char *path, void (*buildStruct)(char **, void *, void *, void *), void *structure1, void *structure2, void *structure3);

#endif
