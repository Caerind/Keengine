#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <functional>
#include <map>
#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <TGUI/TGUI.hpp>

class State
{
    public:
        typedef std::unique_ptr<State> Ptr;

    public:
		State();

		virtual ~State();

		virtual bool handleEvent(sf::Event const& event);

		virtual bool update(sf::Time dt);

		virtual void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

		virtual void onActivate();

		virtual void onDeactivate();

	protected:
		tgui::Gui mGui;
};

class StateManager
{
    public:
		StateManager();

		~StateManager();

		template <typename T>
		void registerState(std::string const& className)
        {
            mFactories[className] = [this]()
            {
                return State::Ptr(new T());
            };
        }

		void handleEvent(sf::Event const& event);

		void update(sf::Time dt);

		void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

		void pushState(std::string const& className);

		void popState();

		void clearStates();

		std::size_t stateCount() const;

		std::vector<std::string> getStateOrder() const;

		std::string getActualState() const;

	protected:
		enum Action
		{
			Push,
			Pop,
			Clear
		};

		struct PendingChange
		{
			explicit PendingChange(Action action, std::string const& id = "");

			Action action;
			std::string id;
		};

		void applyPendingChanges();

		State::Ptr createState(std::string const& id);

	protected:
		std::vector<State::Ptr> mStates;
		std::vector<std::string> mStateOrder;
		std::vector<PendingChange> mPendingList;

		std::map<std::string, std::function<State::Ptr()>> mFactories;
};

#endif // STATEMANAGER_HPP
