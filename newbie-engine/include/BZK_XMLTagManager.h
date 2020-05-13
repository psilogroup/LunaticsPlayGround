/*
 * XMLTagManager.h
 *
 *  Created on: 16/05/2009
 *      Author: newbie
 *
 */

#ifndef __XMLTAGMANAGER_H__
#define __XMLTAGMANAGER_H__

# ifdef WIN32
#  include <windows.h>
# endif

# include <iostream>
# include <fstream>
#include <string>
#include <sstream>
#include <World.h>
#include "BZK_List.h"
#include "BZK_XMLTag.h"
#include <map>

class BZK_XMLTagManager {
public:

	BZK_XMLTagManager(std::string aFileName);

	/**
	 * @brief Adiciona uma nova tag ao gerenciador
	 */
	void Add(BZK_XMLTag* tag);

	/**
	 * @brief processa o arquivo XML e retorna o World
	 * @return World carregado do arquivo XML
	 */
	World* process();

	virtual ~BZK_XMLTagManager();

	std::string fileName;
	std::map<std::string,BZK_XMLTag*> tagList;
};

#endif /* XMLTAGMANAGER_H_ */
