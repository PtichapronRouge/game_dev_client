#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "headers/stateidentifiers.hpp"

class StateStack;

//! La classe abstraite représentant un état du client
/*! Il s'agit d'une classe virtuelle pure, ses dérivés ont vocation à être empilés dans le statestack
 */
class State
{
    public:
        //! Alias de std::unique_ptr<State>
        using   Ptr = std::unique_ptr<State>;

        //! Une struct permettant de réunir tous les composants nécessaires au fonctionnement d'un état
        struct  Context
        {
                //! Le constructeur, qui prend un paramètre par attribut de la struc pour l'initialiser
                /*! \param window L'objet sf::RenderWindow dans lequel tout l'affichage se fait
                 */
                Context(sf::RenderWindow& window);

                //! Un pointeur sur la fenêtre de type RenderWindow dans laquelle tout l'affichage se fait
                sf::RenderWindow* window;
        };

    public:
                //! Le constructeur de la classe State, qui prend en paramètre les objets nécessaire au fonctionnement d'une State
                /*! \param context un State::Context qui contient tous les objets du client dont un State peut avoir besoin
                 * \param statestack une référence sur le StateStack du client, permettant l'interaction avec la pile d'états
                 */
                State(Context context, StateStack& statestack);
                //! Destructeur virtuel de State
        virtual ~State();

                //! La fonction permettant d'ajouter un état dans la pile
                /*! \param id Correspond à l'identification de l'état que l'on souhaite push
                 */
        void    requestStackPush(States::ID id) const;
                //! La fonction permettant de retirer le premier état de la pile
        void    requestStackPop() const;
                //! La fonction permettant de retirer tous les états de la pile
        void    requestStackClear() const;
                        //! La fonction de gestion des évènements
                        /*! Peut renvoyer false pour empêcher les états plus bas dans la pile de gérer l'évènement
                         *  \param event l'évènement à gérer
                         */
        virtual bool    handleEvent(const sf::Event& event) =0;
                        //! La fonction de mise à jour de l'objet
                        /*! \param dt le temps écoulé depuis la frame précédente
                         */
        virtual bool    update(sf::Time dt) = 0;
                        //! La fonction d'affichage de l'objet
        virtual void    draw() =0;

    protected:
                        //! Fonction permettant de récupérer la RenderWindow du Contexte
        sf::RenderWindow* contextWindow() const;

    private:
                        //! Le contexte de l'état, qui contient des pointeurs sur les objets nécessaires
        Context         mContext;
                        //! La pile d'état qui contient l'état
                        /*! L'état peut communiquer avec le statestack grâce aux fonctions requestStack
                         */
        StateStack*     mStateStack;
};

#endif // STATE_HPP
