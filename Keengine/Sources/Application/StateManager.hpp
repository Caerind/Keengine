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

class State
{
    public:
        typedef std::unique_ptr<State> Ptr;

    public:
        State()
        {
        }

        virtual ~State()
        {
        }

        virtual bool handleEvent(sf::Event const& event)
        {
            return true;
        }

        virtual bool update(sf::Time dt)
        {
            return true;
        }

        virtual void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
        {
        }

        virtual void onActivate()
        {
        }

        virtual void onDeactivate()
        {
        }
};

class StateManager
{
    public:
		StateManager()
		{
		}

		~StateManager()
		{
		    for (auto itr = mStates.begin(); itr != mStates.end(); itr++)
            {
                (*itr)->onDeactivate();
            }
            mStates.clear();
		}

		template<typename T>
		void registerState(std::string const& className)
        {
            mFactories[className] = [this]()
            {
                return State::Ptr(new T());
            };
        }

        void handleEvent(sf::Event const& event)
        {
            for (auto itr = mStates.rbegin(); itr != mStates.rend(); itr++)
            {
                if (!(*itr)->handleEvent(event))
                {
                    break;
                }
            }
            applyPendingChanges();
        }

		void update(sf::Time dt = sf::Time::Zero)
        {
            for (auto itr = mStates.rbegin(); itr != mStates.rend(); itr++)
            {
                if (!(*itr)->update(dt))
                {
                    break;
                }
            }
            applyPendingChanges();
        }

		void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default)
		{
            for (auto itr = mStates.begin(); itr != mStates.end(); itr++)
            {
                (*itr)->render(target,states);
            }
        }

		void pushState(std::string const& className)
        {
            mPendingList.push_back(PendingChange(Push, className));
        }

		void popState()
        {
            mPendingList.push_back(PendingChange(Pop));
        }

		void clearStates()
        {
            mPendingList.push_back(PendingChange(Clear));
        }

		std::size_t stateCount() const
        {
            return mStates.size();
        }

	protected:
		enum Action
		{
			Push,
			Pop,
			Clear
		};

		struct PendingChange
		{
			explicit PendingChange(Action action, std::string const& id = "")
			: action(action)
            , id(id)
            {
            }

			Action action;
			std::string id;
		};

		void applyPendingChanges()
        {
            for (PendingChange change : mPendingList)
            {
                switch (change.action)
                {
                    case Action::Push:
                        if (!mStates.empty())
                        {
                            mStates.back()->onDeactivate();
                        }
                        mStates.push_back(createState(change.id));
                        mStates.back()->onActivate();
                        break;

                    case Action::Pop:
                        if (!mStates.empty())
                        {
                            mStates.back()->onDeactivate();
							mStates.pop_back();
                        }
                        if (!mStates.empty())
                        {
                            mStates.back()->onActivate();
                        }
                        break;

                    case Action::Clear:
                        if (!mStates.empty())
                        {
                            mStates.back()->onDeactivate();
                        }
                        mStates.clear();
                        break;
                }
            }
            mPendingList.clear();
        }

		State::Ptr createState(std::string const& id)
		{
            auto found = mFactories.find(id);
            if (found == mFactories.end())
            {
                std::cerr << "State : " << id << " : cant be loaded" << std::endl;
                assert(false);
            }
            return found->second();
        }

	protected:
		std::vector<State::Ptr> mStates;
		std::vector<PendingChange> mPendingList;

		std::map<std::string, std::function<State::Ptr()>> mFactories;
};

#endif // STATEMANAGER_HPP
