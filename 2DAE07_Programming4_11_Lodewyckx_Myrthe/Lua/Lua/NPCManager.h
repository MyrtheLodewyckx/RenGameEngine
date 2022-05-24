#pragma once
#pragma once
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

class NPC
{
	std::string m_name;
	int m_Health = 0;
public:
	explicit NPC(std::string name) : m_name(std::move(name)) {}
	const std::string& get_name() const { return m_name; }
	void SetHealth(int h) { m_Health = h; }
	const int GetHealth() const { return m_Health; }
};

class NPCManager
{
	std::vector<NPC> m_npcs;
public:
	static NPCManager& GetInstance()
	{
		static NPCManager instance{};
		return instance;
	}

	void AddNPC(const std::string&& name)
	{
		m_npcs.push_back(NPC(name));
	}

	void RemoveNPC(const std::string& name)
	{
		m_npcs.erase(std::remove_if(m_npcs.begin(), m_npcs.end(),
			[name](NPC& npc) {return npc.get_name() == name; }), m_npcs.end());
	}

	void SetHealth(int health, const std::string& name)
	{
		std::for_each(m_npcs.begin(), m_npcs.end(), [name, health](NPC& npc) { if (npc.get_name() == name)npc.SetHealth(health); });
	}

	void Dump() const
	{
		std::cout << "Available NPC's:" << std::endl;
		for (const auto& npc : m_npcs)
			std::cout << "NPC " << npc.get_name() << ' ' << std::to_string(npc.GetHealth())<< " hp" << std::endl;
		std::cout << "NPC count:" << m_npcs.size() << std::endl;
	}
};