#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <queue>
#include <functional>
#include <map>
#include <vector>

#include <SFML/Window/Event.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "headers/state.hpp"


//! La classe qui encapsule la machine à état
/*! Fonctionne comme un pile d'états
 */
class StateStack : private sf::NonCopyable
{
    public:
        //! Enumérateur des actions qui peuvent être requises par les state au statestack
        enum class Action
        {
            Push,
            Pop,
            Clear
        };

    public:
                    //! Le constructeur de la statestack
                    /*! \param context le contexte qui contient les objets importants du client et qui sera passé aux états
                     */
        explicit    StateStack(State::Context context);

                    //! La fonction template qui permet d'agrandir la liste des états qui peuvent être créés
                    /*! Rajoute des éléments dans le map mFactories
                     * \param S le type dérivé de State que l'on veut pouvoir créer
                     * \param stateID l'identifiant que l'on veut associer au type dérivé
                     */
        template <typename S>
        void        registerState(States::ID stateID);

                    //! La fonction permettant l'ajout d'un état dans la pile
                    /*! Appelée par la fonction requestStackPush d'un état
                     * Ajoute l'action Push dans la pile de changements en attente
                     * \param stateID L'identifiant de l'état à ajouter
                     */
        void        pushState(States::ID stateID);

                    //! La fonction permettant le retrait du dernier état de la pile
                    //! Ajoute l'action Pop dans la pile de changements en attente
                    /*! Appelée par la fonction requestStackPop d'un état
                     */
        void        popState();

                    //! La fonction permettant le retrait de tous les états de la pile
                    //! Ajoute l'action Clear dans la pile de changements en attente
                    /*! Appelée par la fonction requestStackClear d'un état
                     */
        void        clearStates();

                    //! La fonction permettant la gestion des évènements par le statestack
                    /*! \param event L'evènement à gérer
                     */
        void        handleEvent(const sf::Event& event);

                    //! La fonction permettant la mise à jour du statestack
                    /*! \param dt Le temps écoulé depuis la frame précédente
                     */
        void        update(sf::Time dt);

                    //! La fonction permettant l'affichage du statestack
                    /*! Appelle les fonctions d'affichage des états de la pile en la descendant
                     */
        void        draw();

                    //! Fonction permettant de savoir si la pile d'état est vide
        bool        isEmpty() const;

    private:
                    //! La fonction permettant de créer un état qui pourra être rajouté dans la pile
                    /*! \param stateID L'identifiant de l'état à créer
                     * \return La fonction retourne une unique_ptr sur l'état créé
                     */
        State::Ptr  createState(States::ID stateID);

                    //! Fonction qui applique à la pile tous les changements qui ont été requis
        void        applyPendingChanges();

    private:
        //! Struct qui encapsule une demande de modification de la pile
        /*! Un PendingChange a vocation à être enfilé puis traité par la fonction applyPendingChanges
         */
        struct PendingChange
        {
            //! Constructeur de PendingChange qui initialise ses attributs
            /*! \param action L'Action correspondant au changement requis
             *  \param stateID L'identifiant de l'état lié à l'action (requis dans le cas d'un Push)
             */
            explicit    PendingChange(Action action, States::ID stateID = States::ID::None);

            //! L'Action correspondant au changement requis
            Action      action;
            //! L'identifiant de l'état lié à l'action (requis dans le cas d'un Push)
            States::ID  stateID;
        };

    private:
        //! La pile contenant tous les états
        /*! Il s'agit en fait d'un vector pour pouvoir appeler les update, processEvents et draw
         * de tous les états de la pile sans avoir à depiler - rempiler
         */
        std::vector<State::Ptr>                             mStack;

        //! La file des changements en attente
        /*! Tous les changements de cette file sont traités dans l'ordre par la fonction applyPendingChanges
         */
        std::queue<PendingChange>                           mPendingList;

        //! Le contexte contenant tous les objets importants du client et qui sera passé aux états
        State::Context                                      mContext;

        //! Un map qui permet de lier l'identifiant d'un état avec une fonction créant cet état
        std::map<States::ID, std::function<State::Ptr()>>   mFactories;
};

template <typename S>

void StateStack::registerState(States::ID stateID)
{
    mFactories[stateID] = [this] ()
                            {
                                return State::Ptr(new S(mContext, *this));
                            };
}

#endif // STATESTACK_HPP
