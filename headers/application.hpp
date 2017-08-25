#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/NonCopyable.hpp>


#include "headers/statestack.hpp"

//! Classe principale du client
/*! Contient la boucle principale et la boucle de gestion
 *  des évènements
 */
class Application : public sf::NonCopyable
{
    public:
                    //!Constructeur
                    Application();

                    //!La boucle principale du client
                    /*! Appelle en boucles les fonctions update, processEvents et render
                     */
        void        run();

    private:
                    //! La fonction permettant la mise à jour des composants du client
                    /*! \param dt le temps écoulé depuis la frame précédente
                     */
        void        update(sf::Time dt);
                    //! La fonction permettant à tous les composants du client de gérer les évènements
        void        processEvents();
                    //! La fonction d'affichage de tous les composants
        void        render();

    private:
        //! La fenêtre principale du client
        sf::RenderWindow mWindow;

        //! La machine à état
        /*! La statemachine est sous forme d'une pile d'état
         */
        StateStack  mStateStack;

};

#endif // APPLICATION_HPP
