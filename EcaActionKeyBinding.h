// ...
// ...
// ...

#ifndef ECA_ACTION_KEY_BINDING
#define ECA_ACTION_KEY_BINDING


#include <vector>						// Required for : std::vector


class Model;							// forward declaration
class Controller;						// forward declaration
class View;								// forward declaration


//////////////////////////////////////////////////////////////////////////
//! \brief Table d'association de clés à actions.
//!
//! Cette classe réalise une table d'association (Look Up Table - LUT) 
//! entre une clé (un entier) et une action (une fonction à réaliser).
//! 
//! La classe est conçue ainsi :
//!	- la clé est un entier défini selon un interval donné
//!	- l'action est intimement liée à cette application et prendra en 
//!		paramètre un model et un contrôleur. Ainsi, l'action pourra 
//!		manipuler ces objets pour réaliser diverses tâches.
//!
//! Si, pour une clé donnée, aucune action spécifique n'est définie 
//! et aucune action par défaut n'est définie, l'exécution de la tâche 
//! associée à cette clé ne fait rien.
//!
//! **Attention : ** pour des raisons de performance, aucune 
//! validation n'est faite sur les clés. Ainsi, l'utilisation d'une 
//! clé hors borne donne un comportement non défini.
//!
//! Voici un exemple d'utilisation :
//! \code{.cpp}
//!
//!	// Crée les variables de l'automate
//! EcaModel model;
//! EcaView view;
//! EcaController controller(model, view);
//!
//! // Crée le LUT et détermine 21 actions possibles [-10, 10], les actions sont nulle pour l'instant
//! EcaActionKeyBinding actionKeyBinding(-10, 10); 
//!
//! // Pour chaque action non définie, détermine l'action par défaut à réaliser.
//! actionKeyBinding.setDefaultAction([](EcaModel & model, EcaController & controller){ std::cout << "---default-->" << std::endl; });
//! 
//! // Pour les clés 2, 3, 4 et -8 effectue une tâche particulière.
//! actionKeyBinding.setAction(2, [](EcaModel & model, EcaController & controller){ std::cout << "---2-->" << std::endl; });
//! actionKeyBinding.setAction(3, [](EcaModel & model, EcaController & controller){ std::cout << "---3-->" << std::endl; });
//! actionKeyBinding.setAction(4, [](EcaModel & model, EcaController & controller){ std::cout << "---4-->" << std::endl; });
//! actionKeyBinding.setAction(-8, [](EcaModel & model, EcaController & controller){ std::cout << "---[8]-->" << std::endl; });
//!
//! // La clé 7 réalise la même tâche que la clé 2.
//! actionKeyBinding.setAction(7, 2);
//!	
//! // Exécute toutes les actions possibles
//! for (int i{ -10 }; i < 10; ++i)  {
//!     actionKeyBinding.doActionFromKey(i, model, controller);
//! }
//!
//! \endcode
//! Ce programme produit le résultat suivant :
//! \code{.unparsed}
//! ---default-->
//! ---default-->
//! ---[8]-->
//! ---default-->
//! ---default-->
//! ---default-->
//! ---default-->
//! ---default-->
//! ---default-->
//! ---default-->
//! ---default-->
//! ---default-->
//! ---2-->
//! ---3-->
//! ---4-->
//! ---default-->
//! ---default-->
//! ---2-->
//! ---default-->
//! ---default-->
//! \endcode
//////////////////////////////////////////////////////////////////////////
class EcaActionKeyBinding
{
public:
	//////////////////////////////////////////////////////////////////////////
	//! \brief Le type de la clé.
	//////////////////////////////////////////////////////////////////////////
	using key_t = int;

	//////////////////////////////////////////////////////////////////////////
	//! \brief Signature de fonction pouvant être assignée. 
    //! 
    //! action_t est un type. Il correspond à la déclaration d'une variable de 
    //! type pointeur de fonction. Ce pointeur peut pointer vers une fonction 
    //! prenant en paramètre un EcaModel et un EcaController. Cette fonction 
    //! ne retourne rien.
	//////////////////////////////////////////////////////////////////////////
	using action_t = void(*)(Model & model, Controller & controller, View & view);

    //////////////////////////////////////////////////////////////////////////
    //! \brief Constructeur par défaut. Sert à lier le type `char`. 
    //!
    //! La borne déterminée ici est immuable et réserve la mémoire pour 
    //! toutes les valeurs du type `char` [-128, 127].
    //////////////////////////////////////////////////////////////////////////
	EcaActionKeyBinding();

	//////////////////////////////////////////////////////////////////////////
	//! \brief Constructeur avec valeur d'initialisation. 
	//!
	//! La borne déterminée ici est immuable et réserve la mémoire pour 
	//! toutes les fonctions possiblement incluses dans cette interval, 
	//! c'est à dire : `bindToKey - bindFromKey + 1`.
	//!
	//! \param bindFromKey borne inférieure des clés disponibles
	//! \param bindToKey borne supérieure des clés disponibles
	//////////////////////////////////////////////////////////////////////////
	EcaActionKeyBinding(key_t bindFromKey, key_t bindToKey);

	//////////////////////////////////////////////////////////////////////////
	//! \brief Associe une tâche à une action.
	//!
	//! \param key valeur de la clé
	//! \param action action à réaliser
	//////////////////////////////////////////////////////////////////////////
	void setAction(key_t key, action_t action);

	//////////////////////////////////////////////////////////////////////////
	//! \brief Associe une tâche à une action existante.
	//!
	//! \param keyTarget valeur de la clé cible
	//! \param keySource valeur la clé source
	//////////////////////////////////////////////////////////////////////////
	void setAction(key_t keyTarget, key_t keySource);

	//////////////////////////////////////////////////////////////////////////
	//! \brief Associe une tâche par défaut.
	//!
	//! \param key valeur de la clé cible
	//! \param action action à réaliser
	//////////////////////////////////////////////////////////////////////////
	void setDefaultAction(action_t action);

	//////////////////////////////////////////////////////////////////////////
	//! \brief Associe une tâche par défaut à une tâche existante.
	//!
	//! \param key valeur de la clé source
	//////////////////////////////////////////////////////////////////////////
	void setDefaultAction(key_t key);

	//////////////////////////////////////////////////////////////////////////
	//! \brief Exécute la tâche associée à une clé. Si aucune tâche n'est 
	//! définie pour la clé, réalise la tâche par défaut. Si aucune tâche par 
	//! défaut n'est définie, ne fait rien.
	//!
	//! \param key valeur de la clé
	//! \param model le model à utiliser par la tâche
	//! \param controller le contrôleur à utiliser par la tâche
	//////////////////////////////////////////////////////////////////////////
	void doActionFromKey(key_t key, Model & model, Controller & controller, View & view) const;

	//////////////////////////////////////////////////////////////////////////
	//! \brief Exécute la tâche par défaut. Si aucune tâche par 
	//! défaut n'est définie, ne fait rien.
	//!
	//! \param model le model à utiliser par la tâche
	//! \param controller le contrôleur à utiliser par la tâche
	//////////////////////////////////////////////////////////////////////////
	void doDefaultAction(Model & model, Controller & controller, View & view) const;

private:
	key_t mOffsetKey;
	std::vector<action_t> mBinding;
	action_t mDefaultAction = nullptr;
};


#endif // ECA_ACTION_KEY_BINDING
