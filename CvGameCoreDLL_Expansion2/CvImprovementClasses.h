/*	-------------------------------------------------------------------------------------------------------
	© 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */
#pragma once

#ifndef CIV5_IMPROVEMENT_CLASSES_H
#define CIV5_IMPROVEMENT_CLASSES_H
#include "CvInfos.h"
#include "CustomMods.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  class : CvImprovementResourceInfo
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvImprovementResourceInfo
{
	friend class CvImprovementEntry;

public:
	CvImprovementResourceInfo();
	~CvImprovementResourceInfo();

	int getDiscoverRand() const;
	bool isResourceMakesValid() const;
	bool isResourceTrade() const;
	int getYieldChange(int i) const;

protected:
	int m_iDiscoverRand;
	bool m_bResourceMakesValid;
	bool m_bResourceTrade;

	// Arrays
	int* m_piYieldChange;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:      CvImprovementEntry
//!  \brief		A single improvement available in the game
//
//!  Key Attributes:
//!  - Used to be called CvImprovementInfo
//!  - Populated from XML\Terrain\CIV5Improvements.xml
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvImprovementEntry: public CvBaseInfo
{
public:
	CvImprovementEntry(void);
	~CvImprovementEntry(void);

	virtual bool CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility);

	int GetGoldMaintenance() const;
	int GetCultureBombRadius() const;

#if defined(MOD_GLOBAL_STACKING_RULES)
	int GetAdditionalUnits() const;
#endif

	int GetTilesPerGoody() const;
	int GetGoodyUniqueRange() const;
	int GetFeatureGrowthProbability() const;
	int GetUpgradeTime() const;
	int GetRiverSideUpgradeMod() const;
	int GetCoastalLandUpgradeMod() const;
	int GetHillsUpgradeMod() const;
	int GetFreshWaterUpgradeMod() const;
	int GetDefenseModifier() const;
	int GetNearbyEnemyDamage() const;
	int GetPillageGold() const;
	int GetResourceExtractionMod() const;
	int GetLuxuryCopiesSiphonedFromMinor() const;
	int GetImprovementPillage() const;
	void SetImprovementPillage(int i);
	int GetImprovementUpgrade() const;
	void SetImprovementUpgrade(int i);
	int GetRequiresXAdjacentLand() const;
#if defined(MOD_API_EXTENSIONS)
	int GetRequiresXAdjacentWater() const;
#endif

#if defined(MOD_ROG_CORE)
	int GetWonderProductionModifier() const;
	int GetNearbyFriendHeal() const;
	int GetResourceFromImprovement() const;
	int GetResourceQuantityFromImprovement() const;
#endif

#if defined(MOD_IMPROVEMENTS_CREATE_ITEMS)
	int GetCreateItemMod() const;
	int GetCreatedResourceQuantity() const;
	int GetNewImprovement() const;
	int GetNewFeature() const;

	int GetCreateResource(CvPlot* pPlot) const;
#endif
	UnitClassTypes GetForbidSameBuildUnitClasses() const;
	int GetExtraScore() const;

#ifdef MOD_GLOBAL_PROMOTIONS_REMOVAL
	bool IsClearNegativePromotions() const;
#endif

#if defined(MOD_GLOBAL_RELOCATION)
	bool IsAllowsRebaseTo() const;
	bool IsAllowsAirliftFrom() const;
	bool IsAllowsAirliftTo() const;
#endif

	bool IsHillsMakesValid() const;
	bool IsMountainsMakesValid() const;
#if defined(MOD_GLOBAL_PASSABLE_FORTS)
	bool IsMakesPassable() const;
#endif
#if defined(MOD_API_PLOT_BASED_DAMAGE)
	bool IsNegatesTerrainDamage() const;
	bool IsNegatesFeatureDamage() const;
#endif
#if defined(MOD_GLOBAL_NO_FOLLOWUP)
	bool IsNoFollowup() const;
#endif
	bool IsFreshWaterMakesValid() const;
	bool IsRiverSideMakesValid() const;
	bool IsNoFreshWater() const;
	bool IsFreshWater() const;
	bool IsNoFeature() const;
	bool IsNoRemove() const;
	int GetNumWaterPlotMakesValid() const;
#if defined(MOD_API_EXTENSIONS)
	bool IsAddsFreshWater() const;
#endif
	bool IsRequiresFlatlands() const;
	bool IsRequiresFlatlandsOrFreshWater() const;
	bool IsRequiresFeature() const;
	bool IsRequiresImprovement() const;
	bool IsRemovesResource() const;
	bool IsPromptWhenComplete() const;
	bool IsWater() const;
	bool IsNoLake() const;
	bool IsCoastal() const;
	bool IsDestroyedWhenPillaged() const;
	bool IsDisplacePillager() const;
	bool IsBuildableOnResources() const;
	bool IsBarbarianCamp() const;
	bool IsGoody() const;
	bool IsPermanent() const;
	bool IsOutsideBorders() const;
	bool IsInAdjacentFriendly() const;
	bool IsIgnoreOwnership() const;
	bool IsOnlyCityStateTerritory() const;
	bool IsNoTwoAdjacent() const;
	bool IsAdjacentLuxury() const;
	bool IsAllowsWalkWater() const;
	bool IsCreatedByGreatPerson() const;
	bool IsSpecificCivRequired() const;

	ImprovementTypes GetRequiredAdjacentImprovement() const;
	bool IsRequiredAdjacentCity() const;
	bool IsRemoveWhenSetNoFuture() const;

	CivilizationTypes GetRequiredCivilization() const;

	const char* GetArtDefineTag() const;
	void SetArtDefineTag(const char* szVal);

	ImprovementUsageTypes GetImprovementUsage() const;
	void SetImprovementUsage(const ImprovementUsageTypes usageType);

	int GetWorldSoundscapeScriptId() const;

	// Arrays

	int GetResourceQuantityRequirement(int i) const;

	int GetPrereqNatureYield(int i) const;
	int* GetPrereqNatureYieldArray();
	int GetYieldChange(int i) const;
	int* GetYieldChangeArray();
	int GetYieldChangePerEra(int i) const;
	int GetRiverSideYieldChange(int i) const;
	int* GetRiverSideYieldChangeArray();
	int GetCoastalLandYieldChange(int i) const;
	int* GetCoastalLandYieldChangeArray();
	int GetHillsYieldChange(int i) const;
	int* GetHillsYieldChangeArray();
	int GetNoFreshWaterYieldChange(int i) const;
	int* GetNoFreshWaterYieldChangeArray();				// For Moose - CvWidgetData XXX
	int GetFreshWaterYieldChange(int i) const;
	int* GetFreshWaterYieldChangeArray();				// For Moose - CvWidgetData XXX
	int GetAdjacentCityYieldChange(int i) const;
	int* GetAdjacentCityYieldChangeArray();

	bool GetTerrainMakesValid(int i) const;
	bool GetFeatureMakesValid(int i) const;
	bool IsFeatureNeeded() const;
	bool GetFeaturesNeeded(int i) const;
	bool GetImprovementMakesValid(int i) const;

#if defined(MOD_API_UNIFIED_YIELDS)
	int GetAdjacentSameTypeYield(int i) const;
#endif

#if defined(MOD_API_VP_ADJACENT_YIELD_BOOST)
	int GetAdjacentImprovementYieldChanges(int i, int j) const;
#endif

	bool IsAdjacentResourceYieldChanges() const;
	int GetAdjacentResourceYieldChanges(int i, int j) const;

	bool IsAdjacentTerrainYieldChanges() const;
	int GetAdjacentTerrainYieldChanges(int i, int j) const;
	int GetAdjacentTerrainYieldChanges(const CvPlot& pPlot, YieldTypes eYield) const;

	bool IsAdjacentFeatureYieldChanges() const;	
	int GetAdjacentFeatureYieldChanges(int i, int j) const;

#if defined(MOD_ROG_CORE)
	int GetFeatureYieldChanges(int i, int j) const;
#endif
	int GetTerrainYieldChanges(int i, int j) const;
	int GetTechYieldChanges(int i, int j) const;
	int* GetTechYieldChangesArray(int i);
	int GetTechNoFreshWaterYieldChanges(int i, int j) const;
	int* GetTechNoFreshWaterYieldChangesArray(int i);
	int GetTechFreshWaterYieldChanges(int i, int j) const;
	int* GetTechFreshWaterYieldChangesArray(int i);
	int GetRouteYieldChanges(int i, int j) const;
	int* GetRouteYieldChangesArray(int i);				// For Moose - CvWidgetData XXX

#if defined(MOD_IMPROVEMENT_TRADE_ROUTE_BONUSES)
	int GetTradeRouteYieldChanges(int i, int j) const;
	int* GetTradeRouteYieldChangesArray(int i);				// For Moose - CvWidgetData XXX
#endif

	int  GetImprovementResourceYield(int i, int j) const;
	bool IsImprovementResourceMakesValid(int i) const;
	bool IsImprovementResourceTrade(int i) const;
	int  GetImprovementResourceDiscoverRand(int i) const;

	int  GetFlavorValue(int i) const;

#ifdef MOD_IMPROVEMENTS_UPGRADE
	bool GetEnableXP() const;

	bool GetEnableUpgrade() const;
	int GetUpgradeXP() const;
	ImprovementTypes GetUpgradeImprovementType() const;

	bool GetEnableDowngrade() const;
	ImprovementTypes GetDowngradeImprovementType() const;
#endif

#ifdef MOD_IMPROVEMENTS_YIELD_CHANGE_PER_UNIT
	struct YieldChangesPerUnit {
		YieldTypes eYieldType = NO_YIELD;
		int iYield = 0;
		UnitTypes eUnitType = NO_UNIT;
		PromotionTypes ePromotionType = NO_PROMOTION;
	};

	std::vector<YieldChangesPerUnit>& GetYieldChangesPerUnitVec();
#endif

#ifdef MOD_IMPROVEMENTS_UNIT_XP_PER_TURN
	struct UnitXPPerTurn {
		int iValue = 0;
		UnitTypes eUnitType = NO_UNIT;
		PromotionTypes ePromotionType = NO_PROMOTION;
	};

	std::vector<UnitXPPerTurn>& GetUnitXPPerTurnVec();
#endif

	//---------------------------------------PROTECTED MEMBER VARIABLES---------------------------------
protected:
	void InitImprovementResourceList(CvImprovementResourceInfo** ppImprovementResource, int iListLen);

	int m_iGoldMaintenance;
	int m_iCultureBombRadius;

#if defined(MOD_GLOBAL_STACKING_RULES)
	int m_iAdditionalUnits;
#endif

	int m_iTilesPerGoody;
	int m_iGoodyUniqueRange;
	int m_iFeatureGrowthProbability;
	int m_iUpgradeTime;
	int m_iRiverSideUpgradeMod;
	int m_iCoastalLandUpgradeMod;
	int m_iHillsUpgradeMod;
	int m_iFreshWaterUpgradeMod;
	int m_iDefenseModifier;
	int m_iNearbyEnemyDamage;
	int m_iPillageGold;
	int m_iResourceExtractionMod;
	int m_iLuxuryCopiesSiphonedFromMinor;
	int m_iImprovementPillage;
	int m_iImprovementUpgrade;
	int m_iRequiresXAdjacentLand;
#if defined(MOD_API_EXTENSIONS)
	int m_iRequiresXAdjacentWater;
#endif

#if defined(MOD_ROG_CORE)
	int m_iWonderProductionModifier;
	int m_iNearbyFriendHeal;

	int m_iImprovementResource;
	int m_iImprovementResourceQuantity;
#endif

#if defined(MOD_IMPROVEMENTS_CREATE_ITEMS)
	int m_iCreateItemMod;
	int m_iCreatedResourceQuantity;
	int m_iSetNewImprovement;
	int m_iSetNewFeature;

	int* m_iCreateResourceList;
	int* m_iCreateTerrainList;
	bool* m_iCreateTerrainOnlyList;
	int* m_iCreateFeatureList;
	bool* m_iCreateFeatureOnlyList;
#endif
	int m_iForbidSameBuildUnitClasses;
	int m_iExtraScore;

#ifdef MOD_GLOBAL_PROMOTIONS_REMOVAL
	bool m_bClearNegativePromotions;
#endif

#if defined(MOD_GLOBAL_RELOCATION)
	bool m_bAllowsRebaseTo;
	bool m_bAllowsAirliftFrom;
	bool m_bAllowsAirliftTo;
#endif

	bool m_bHillsMakesValid;
	bool m_bMountainsMakesValid;
#if defined(MOD_GLOBAL_PASSABLE_FORTS)
	bool m_bMakesPassable;
#endif
#if defined(MOD_API_PLOT_BASED_DAMAGE)
	bool m_bNegatesTerrainDamage;
	bool m_bNegatesFeatureDamage;
#endif
#if defined(MOD_GLOBAL_NO_FOLLOWUP)
	bool m_bNoFollowup;
#endif
	bool m_bFreshWaterMakesValid;
	bool m_bRiverSideMakesValid;
	bool m_bNoFreshWater;
	bool m_bIsFreshWater;
	bool m_bNoFeature;
	bool m_bNoRemove;
	int m_iNumWaterPlotMakesValid;
#if defined(MOD_API_EXTENSIONS)
	bool m_bAddsFreshWater;
#endif
	bool m_bRequiresFlatlands;
	bool m_bRequiresFlatlandsOrFreshWater;
	bool m_bRequiresFeature;
	bool m_bRequiresImprovement;
	bool m_bRemovesResource;
	bool m_bPromptWhenComplete;
	bool m_bWater;
	bool m_bNoLake;
	bool m_bCoastal;
	bool m_bDestroyedWhenPillaged;
	bool m_bDisplacePillager;
	bool m_bBuildableOnResources;
	bool m_bBarbarianCamp;
	bool m_bGoody;
	bool m_bPermanent;
	bool m_bOutsideBorders;
	bool m_bInAdjacentFriendly;
	bool m_bIgnoreOwnership;
	bool m_bOnlyCityStateTerritory;
	bool m_bNoTwoAdjacent;
    bool m_bAdjacentLuxury;
	bool m_bAllowsWalkWater;
	bool m_bCreatedByGreatPerson;
	bool m_bSpecificCivRequired;

	ImprovementTypes m_iRequiredAdjacentImprovement = NO_IMPROVEMENT;
	bool m_bRequiredAdjacentCity = false;
	bool m_bRemoveWhenSetNoFuture = false;

	CvString m_strArtDefineTag;
	ImprovementUsageTypes m_eImprovementUsageType;
	CivilizationTypes m_eRequiredCivilization;

	int m_iWorldSoundscapeScriptId;

	// Arrays
	int* m_piResourceQuantityRequirements;

	int* m_piPrereqNatureYield;
	int* m_piYieldChange;
	int* m_piYieldPerEra;
	int* m_piRiverSideYieldChange;
	int* m_piCoastalLandYieldChange;
	int* m_piHillsYieldChange;
	int* m_piFreshWaterChange;
	int* m_piAdjacentCityYieldChange;
	int* m_piFlavorValue;

	bool* m_pbTerrainMakesValid;
	bool* m_pbFeatureMakesValid;
	bool m_bFeatureNeeded;
	bool* m_pbFeaturesNeeded;
	bool* m_pbImprovementMakesValid;

#if defined(MOD_API_VP_ADJACENT_YIELD_BOOST)
	int** m_ppiAdjacentImprovementYieldChanges;
#endif

	int m_iAdjacentTerrainYieldChangesCount;
	int m_iAdjacentResourceYieldChangesCount;
	int m_iAdjacentFeatureYieldChangesCount;
	int** m_ppiAdjacentTerrainYieldChanges;
	int** m_ppiAdjacentResourceYieldChanges;
	int** m_ppiAdjacentFeatureYieldChanges;
#if defined(MOD_ROG_CORE)
	int** m_ppiFeatureYieldChanges;
#endif
	int** m_ppiTerrainYieldChanges;

	int** m_ppiTechYieldChanges;
	int** m_ppiTechNoFreshWaterYieldChanges;
	int** m_ppiTechFreshWaterYieldChanges;
	int** m_ppiRouteYieldChanges;

#if defined(MOD_IMPROVEMENT_TRADE_ROUTE_BONUSES)
	int** m_ppiTradeRouteYieldChanges;
#endif

#ifdef MOD_IMPROVEMENTS_UPGRADE
	bool m_bEnableXP = false;

	bool m_bEnableUpgrade = false;
	int m_iUpgradeXP = -1;
	ImprovementTypes m_eUpgradeImprovementType = NO_IMPROVEMENT;

	bool m_bEnableDowngrade = false;
	ImprovementTypes m_eDowngradeImprovementType = NO_IMPROVEMENT;
#endif

#ifdef MOD_IMPROVEMENTS_YIELD_CHANGE_PER_UNIT
	std::vector<YieldChangesPerUnit> m_vYieldChangesPerUnit;
#endif

#ifdef MOD_IMPROVEMENTS_UNIT_XP_PER_TURN
	std::vector<UnitXPPerTurn> m_vUnitXPPerTurn;
#endif

	CvImprovementResourceInfo* m_paImprovementResource;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:      CvImprovementXMLEntries
//!  \brief		Game-wide information about improvements
//
//! Key Attributes:
//! - Plan is it will be contained in CvGameRules object within CvGame class
//! - Populated from XML\Terrain\CIV5ImprovementInfo.xml
//! - Contains an array of CvImprovementEntry from the above XML file
//! - One instance for the entire game
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvImprovementXMLEntries
{
public:
	CvImprovementXMLEntries(void);
	~CvImprovementXMLEntries(void);

	// Accessor functions
	std::vector<CvImprovementEntry*>& GetImprovementEntries();
	int GetNumImprovements();
	_Ret_maybenull_ CvImprovementEntry* GetEntry(int index);
	CvImprovementEntry* GetImprovementForResource(int eResource);

	// Binary cache functions
	void DeleteArray();

private:
	std::vector<CvImprovementEntry*> m_paImprovementEntries;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Helper Functions to serialize arrays of variable length (based on number of improvements defined in game)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace ImprovementArrayHelpers
{
void Read(FDataStream& kStream, int* paiImprovementArray);
void Write(FDataStream& kStream, int* paiImprovementArray, int iArraySize);
void ReadYieldArray(FDataStream& kStream, int** ppaaiImprovementYieldArray, int iNumYields);
void WriteYieldArray(FDataStream& kStream, int** ppaaiImprovementYieldArray, int iArraySize);
}

#endif //CIV5_IMPROVEMENT_CLASSES_H
