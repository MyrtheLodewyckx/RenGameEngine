#include <algorithm>
#include <vector>
#include <glm/vec2.hpp>
#include "../LevelManager.h"

float GetHeuristicCost(Cell pStartNode, Cell pEndNode)
{
	glm::vec2 toDestination = glm::vec2{ pEndNode.GetRectPoints().x, pEndNode.GetRectPoints().y } - glm::vec2{ pStartNode.GetRectPoints().x, pStartNode.GetRectPoints().y };
	return std::max(abs(toDestination.x), abs(toDestination.y));
}

struct NodeRecord
{
	Cell* pNode = nullptr;
	int direction{};
	float costSoFar = 0.f; // accumulated g-costs of all the connections leading up to this one
	float estimatedTotalCost = 0.f; // f-cost (= costSoFar + h-cost)

	bool operator==(const NodeRecord& other) const
	{
		return pNode == other.pNode
			&& direction == other.direction
			&& costSoFar == other.costSoFar
			&& estimatedTotalCost == other.estimatedTotalCost;
	};

	bool operator<(const NodeRecord& other) const
	{
		return estimatedTotalCost < other.estimatedTotalCost;
	};
};

std::vector<Cell> FindPath(Cell* pStartNode, Cell* pGoalNode)
{
	std::vector<Cell> path{};
	std::vector<NodeRecord> openList{};
	std::vector<NodeRecord> closedList{};

	//
	//dae::LevelManager::GetInstance().GetDirectionFlags({ pStartNode->boundingBox.x +1,pStartNode->boundingBox.y + 1 }, direction);
	NodeRecord currentRecord{ pStartNode,0 };
	currentRecord.estimatedTotalCost = GetHeuristicCost(*pStartNode, *pGoalNode);
	openList.emplace_back(currentRecord);

	while (!openList.empty())
	{
		currentRecord = *std::min_element(openList.begin(), openList.end());

		if (currentRecord.direction != 0)
			if (dae::LevelManager::GetInstance().GetTo({ currentRecord.pNode->boundingBox.x + 1, currentRecord.pNode->boundingBox.y + 1 }, currentRecord.direction) == pGoalNode)
				break;

		int direction{};
		dae::LevelManager::GetInstance().GetDirectionFlags({ currentRecord.pNode->boundingBox.x + 1, currentRecord.pNode->boundingBox.y + 1 }, direction);
		int dirToLoop{ 1 };
		for (int i{ 0 }; i < 4; ++i)
		{
			if (!((direction & dirToLoop) == dirToLoop))
				continue;

			const float costSoFar = currentRecord.costSoFar + 1;

			//Check if on closed list
			for (auto record : closedList)
			{
				if (record.pNode == dae::LevelManager::GetInstance().GetTo({ record.pNode->boundingBox.x + 1, record.pNode->boundingBox.y + 1 }, dirToLoop))
				{
					if (costSoFar < record.costSoFar)
					{
						auto itr = std::remove(closedList.begin(), closedList.end() - 1, record);
						closedList.erase(itr);
					}
					else continue;
				}
			}

			//check if on open list
			for (auto record : openList)
			{
				if (record.pNode == dae::LevelManager::GetInstance().GetTo({ record.pNode->boundingBox.x + 1, record.pNode->boundingBox.y + 1 }, dirToLoop))
				{
					if (costSoFar < record.costSoFar)
					{
						openList.erase(std::remove(openList.begin(), openList.end() - 1, record));
					}
					else continue;
				}
			}

			NodeRecord newRec{ dae::LevelManager::GetInstance().GetTo({ currentRecord.pNode->boundingBox.x + 1, currentRecord.pNode->boundingBox.y + 1 },dirToLoop),dirToLoop };
			newRec.costSoFar = costSoFar;
			openList.emplace_back(newRec);

			dirToLoop = dirToLoop << 1;
		}
		openList.erase(std::remove(openList.begin(), openList.end(), currentRecord));
		closedList.emplace_back(currentRecord);
	}

	closedList.insert(closedList.end(), openList.begin(), openList.end());

	while (currentRecord.pNode != pStartNode)
	{
		path.emplace_back(*currentRecord.pNode);


		for (auto record : closedList)
		{
			if (record.pNode == dae::LevelManager::GetInstance().GetTo({ currentRecord.pNode->boundingBox.x + 1, currentRecord.pNode->boundingBox.y + 1 }, currentRecord.direction))
			{
				currentRecord = record;
				break;
			}
		}
	}

	path.emplace_back(*pStartNode);
	std::reverse(path.begin(), path.end());
	return path;
}
