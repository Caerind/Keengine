#ifndef KE_SERIALIZER_HPP
#define KE_SERIALIZER_HPP

#include <map>
#include <vector>
#include "String.hpp"
#include "Serializable.hpp"

namespace ke
{

class Serializer
{
	public:
		Serializer();

		// Write
		virtual void create(const std::string& identifier);

		template <typename T>
		void save(const std::string& identifier, const T& value)
		{
		}

		virtual void save(const std::string& identifier, const std::string& value);

		template <typename T>
		void save(const std::string& identifier, const std::vector<T>& vector)
		{
			create(identifier);
			save("size", vector.size());
			for (std::size_t i = 0; i < vector.size(); ++i)
			{
				save("i" + std::to_string(i), vector.at(i));
			}
			end();
		}

		template <typename T>
		void saveComplex(const std::string& identifier, const std::vector<T>& vector)
		{
			create(identifier);
			save("size", vector.size());
			for (std::size_t i = 0; i < vector.size(); ++i)
			{
				vector.at(i).serialize(*this, "i" + std::to_string(i));
			}
			end();
		}

		template <typename K, typename T>
		void save(const std::string& identifier, const std::map<K, T>& map)
		{
			create(identifier);
			save("size", map.size());
			std::size_t i = 0;
			for (auto itr = map.begin(); itr != map.end(); itr++)
			{
				save("i" + std::to_string(i), std::string(toString<K>(itr->first) + "||" + toString<T>(itr->second)));
				i++;
			}
			end();
		}

		template <typename K, typename T>
		void saveComplex(const std::string& identifier, const std::map<K, T>& map)
		{
			create(identifier);
			save("size", map.size());
			std::size_t i = 0;
			for (auto itr = map.begin(); itr != map.end(); itr++)
			{
				std::string key = toString<K>(itr->first);
				save("i" + std::to_string(i), key);
				itr->second.serialize(*this, key);
				i++;
			}
			end();
		}

		template <typename T>
		void saveComplex(std::string const& identifier, T const& t)
		{
			t.serialize(*this, identifier);
		}

		virtual void end();

		// Read
		virtual bool read(const std::string& identifier);

		virtual bool load(const std::string& identifier, std::string& value);

		template <typename T>
		bool load(const std::string& identifier, T& value)
		{
			return false;
		}

		template <typename T>
		T load(const std::string& identifier)
		{
			T temp;
			load(identifier, temp);
			return temp;
		}

		template <typename T>
		bool load(const std::string& identifier, std::vector<T>& vector)
		{
			bool ret = true;
			if (read(identifier))
			{
				std::size_t size;
				if (load("size", size))
				{
					vector.clear();
					for (std::size_t i = 0; i < size; ++i)
					{
						T value;
						if (!load("i" + std::to_string(i), value))
						{
							value = T();
							ret = false;
						}
						vector.push_back(value);
					}
					end();
					return ret;
				}
				end();
			}
			return false;
		}

		template <typename T>
		bool loadComplex(const std::string& identifier, std::vector<T>& vector)
		{
			bool ret = true;
			if (read(identifier))
			{
				std::size_t size;
				if (load("size", size))
				{
					vector.clear();
					for (std::size_t i = 0; i < size; ++i)
					{
						vector.push_back(T());
						if (!loadComplex("i" + std::to_string(i), vector.back()))
						{
							ret = false;
						}
					}
					end();
					return ret;
				}
				end();
			}
			return false;
		}

		template <typename K, typename T>
		bool load(const std::string& identifier, std::map<K, T>& map)
		{
			bool ret = true;
			if (read(identifier))
			{
				std::size_t size;
				if (load("size", size))
				{
					map.clear();
					for (std::size_t i = 0; i < size; ++i)
					{
						std::string temp;
						if (load("i" + std::to_string(i), temp))
						{
							std::size_t f = temp.find_first_of("||");
							K k;
							T t;
							if (f != std::string::npos)
							{
								k = fromString<K>(temp.substr(0, f));
								t = fromString<T>(temp.substr(f + 2));
							}
							else
							{
								ret = false;
							}
							map.emplace(k, t);
						}
						else
						{
							end();
							return false;
						}
					}
					end();
					return ret;
				}
				end();
			}
			return false;
		}

		template <typename K, typename T>
		bool loadComplex(const std::string& identifier, std::map<K, T>& map)
		{
			bool ret = true;
			if (read(identifier));
			{
				std::size_t size;
				if (load("size", size))
				{
					map.clear();
					for (std::size_t i = 0; i < size; ++i)
					{
						std::string key;
						if (load("i" + toString(i), key))
						{
							T t;
							if (!loadComplex(key, t))
							{
								ret = false;
								t = T();
							}
							map.emplace(fromString<K>(key), t);
						}
						else
						{
							end();
							return false;
						}
					}
					end();
					return ret;
				}
				end();
			}
			return false;
		}

		template <typename T>
		bool loadComplex(const std::string& identifier, T& t)
		{
			return t.deserialize(*this, identifier);
		}
};

} // namespace ke

#endif // KE_SERIALIZER_HPP
