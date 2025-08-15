/**
 *
 * pixengeo
 *
 * CEA CNRS INRIA LOGICIEL LIBRE
 *
 * Copyright(c) 2014-2025 CHOQUET Olivier
 *
 * This software is a computer program whose purpose is to provide
 * modern C++ cross-platform 2D game engine.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 */

#pragma once
#if 0
#include <vector>
#include <memory>
#include <unordered_map>>

namespace pxg::map
{

	class object 
	{
		std::int32_t	m_id;
		std::string		m_name;
	};

	class layer 
	{
		std::int32_t	m_id;
		std::string		m_name;
	};

	class tile_layer : public layer 
	{
	};

	class image_layer : public layer
	{
	};

	class object_layer : public layer 
	{
		
		std::vector<std::shared_ptr<object>> m_objects;
	};

	class group_layer : public layer
	{
		std::vector<std::shared_ptr<layer>> m_layers;
	};

	class map 
	{
		// -> couleur d'arri�re-plan
		std::vector<std::shared_ptr<layer>> m_layers;

		std::unordered_map<std::int32_t, std::shared_ptr<layer>> m_layers;
		std::unordered_map<std::int32_t, std::shared_ptr<object>> m_objects;
	};


	class rectangle_object : public object 
	{
		std::size_t		m_x;
		std::size_t		m_y;
		std::size_t		m_width;
		std::size_t		m_height;
	};

	class circle_object : public object 
	{	
		std::size_t		m_x;
		std::size_t		m_y;
		std::size_t		m_width;
		std::size_t		m_height;
	};

	class point_object : public object 
	{
		std::size_t		m_x;
		std::size_t		m_y;
	};

	class tile_object : public object 
	{
		std::size_t		m_x;
		std::size_t		m_y;
		std::size_t		m_width;
		std::size_t		m_height;
		std::int32_t	m_gid;
	};

	class text_object : public object {};

	// pixengeo-defined classes :
	class collider_rectangle_object : public rectangle_object {};
	class collider_point_object : public point_object {};
	class collider_circle_object : public circle_object {};
	
	class tile_map_layer : public tile_layer {};
	class view_group_layer : public group_layer {};

	// user-defined classes examples :
	class general_map : public map {}; // logique g�n�rale de la pi�ce

	class project {};

	class my_project : public project {}; // logique g�n�rale du jeu
	// pr�sente 

	class local_factory {};
	class pixengeo_local_factory : public local_factory {};
	class global_factory
	{
		std::vector<std::unique_ptr<local_factory>> m_factories;
	};


	/* logique g�n�rale du moteur
	
		CHARGEMENT DU MOTEUR
		
		1. initialisation du logger
		2. parse de la ligne de commande
		3. chargement de la dll du jeu
		4. cr�ation de la fen�tre
		5. cr�ation du renderer
		6. r�cup�ration du projet depuis la dll
			6.1. chargement du projet et r�cup�ration des cartes
		
		BOUCLE PRINCIPALE

		1. sous condition: d�marrage de la carte / arr�t de la pr�c�dente
		2. polling des �v�nements
		3. mise � jour de la carte
		4. dessin de la carte

		DECHARGEMENT DU MOTEUR

		1. d�chargement de la dll du jeu
		2. d�chargement du moteur

	*/

}
#endif