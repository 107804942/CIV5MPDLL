/*	-------------------------------------------------------------------------------------------------------
	© 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */
#include "CvBuildingClasses.h"
#include "CvGameCoreDLLPCH.h"
#include "ICvDLLUserInterface.h"
#include "CvGameCoreUtils.h"
#include "CvInternalGameCoreUtils.h"
#include "FStlContainerSerialization.h"
#include "CvEnumSerialization.h"
#include "CvDLLUtilDefines.h"
#include "CvDllCity.h"
#include "CvDllPlot.h"
#include "CvInfosSerializationHelper.h"

// include after all other headers
#include "LintFree.h"

/// Constructor
CvBuildingEntry::CvBuildingEntry(void):

	m_iBuildingClassType(NO_BUILDINGCLASS),
	m_pkBuildingClassInfo(NULL),
	m_iNearbyTerrainRequired(NO_VICTORY),
	m_iProhibitedCityTerrain(NO_VICTORY),
	m_iVictoryPrereq(NO_VICTORY),
	m_iFreeStartEra(NO_ERA),
	m_iMaxStartEra(NO_ERA),
	m_iObsoleteTech(NO_TECH),
	m_iEnhancedYieldTech(NO_TECH),
	m_iTechEnhancedTourism(0),
	m_iGoldMaintenance(0),
	m_iReplacementBuildingClass(NO_BUILDINGCLASS),
	m_iPrereqAndTech(NO_TECH),
	m_iTechNoPrereqClasses(NO_TECH),
	m_iPolicyBranchType(NO_POLICY_BRANCH_TYPE),
	m_iPolicyNeededType(NO_POLICY),
	m_bPuppetPurchaseOverride(false),
	m_bAllowsPuppetPurchase(false),
	m_iSpecialistType(NO_SPECIALIST),
	m_iSpecialistCount(0),
	m_iSpecialistExtraCulture(0),
	m_iGreatPeopleRateChange(0),
	m_eGreatWorkSlotType(NO_GREAT_WORK_SLOT),
#if defined(MOD_GLOBAL_GREATWORK_YIELDTYPES)
	m_eGreatWorkYieldType(YIELD_CULTURE),
#endif
	m_iGreatWorkCount(0),
	m_eFreeGreatWork(NO_GREAT_WORK),
	m_iFreeBuildingClass(NO_BUILDINGCLASS),
	m_iFreeBuildingThisCity(NO_BUILDINGCLASS),
	m_iFreePromotion(NO_PROMOTION),
	m_iFreePromotion2(NO_PROMOTION),
	m_iFreePromotion3(NO_PROMOTION),
	m_iTrainedFreePromotion(NO_PROMOTION),
	m_iFreePromotionRemoved(NO_PROMOTION),
	m_iProductionCost(0),
	m_iFaithCost(0),
	m_iLeagueCost(0),
	m_iNumCityCostMod(0),
	m_iHurryCostModifier(0),
	m_iNumCitiesPrereq(0),
	m_iUnitLevelPrereq(0),
	m_iCultureRateModifier(0),
	m_iGlobalCultureRateModifier(0),
	m_iGreatPeopleRateModifier(0),
	m_iGlobalGreatPeopleRateModifier(0),
	m_iGreatGeneralRateModifier(0),
	m_iGreatPersonExpendGold(0),
	m_iUnitUpgradeCostMod(0),
	m_iGoldenAgeModifier(0),
	m_iFreeExperience(0),
	m_iGlobalFreeExperience(0),
	m_iFoodKept(0),
	m_bAirlift(false),
	m_iAirModifier(0),
	m_iNukeModifier(0),
	m_iNukeExplosionRand(0),
	m_iWorkerSpeedModifier(0),
	m_iMilitaryProductionModifier(0),
	m_iSpaceProductionModifier(0),
	m_iGlobalSpaceProductionModifier(0),
	m_iMinAreaSize(0),
	m_iConquestProbability(0),
	m_iHealRateChange(0),
	m_iHappiness(0),
	m_iUnmoddedHappiness(0),
	m_iUnhappinessModifier(0),
	m_iHappinessPerCity(0),
	m_iHappinessPerXPolicies(0),
	m_iCityCountUnhappinessMod(0),
	m_bNoOccupiedUnhappiness(false),
	m_bNotNeedOccupied(false),
	m_iGlobalPopulationChange(0),
	m_iTechShare(0),
	m_iFreeTechs(0),
	m_iFreePolicies(0),
	m_iFreeGreatPeople(0),
	m_iMedianTechPercentChange(0),
	m_iGold(0),
	m_bNearbyMountainRequired(false),
	m_bAllowsRangeStrike(false),
	m_iDefenseModifier(0),
	m_iGlobalDefenseModifier(0),
	m_iExtraCityHitPoints(0),
	m_iMissionType(NO_MISSION),
	m_iMinorFriendshipChange(0),
	m_iVictoryPoints(0),
	m_iExtraMissionarySpreads(0),
	m_iReligiousPressureModifier(0),
	m_iEspionageModifier(0),
	m_iGlobalEspionageModifier(0),
	m_iGlobalEspionageSpeedModifier(0),
	m_iExtraSpies(0),
	m_iSpyRankChange(0),
	m_iTradeRouteRecipientBonus(0),
	m_iTradeRouteTargetBonus(0),
	m_iNumTradeRouteBonus(0),
	m_iTradeRouteSeaDistanceModifier(0),
	m_iTradeRouteSeaGoldBonus(0),
	m_iTradeRouteLandDistanceModifier(0),
	m_iTradeRouteLandGoldBonus(0),
#ifdef MOD_BUILDINGS_GOLDEN_AGE_EXTEND
	m_iGoldenAgeUnitCombatModifier(0),
	m_iGoldenAgeMeterMod(0),
#endif
#if defined(MOD_RELIGION_CONVERSION_MODIFIERS)
	m_iConversionModifier(0),
	m_iGlobalConversionModifier(0),
#endif
	m_iInstantSpyRankChange(0),
	m_iLandmarksTourismPercent(0),
	m_iInstantMilitaryIncrease(0),
	m_iGreatWorksTourismModifier(0),
	m_iXBuiltTriggersIdeologyChoice(0),
	m_iGreatScientistBeakerModifier(0),
	m_iExtraLeagueVotes(0),
	m_iPreferredDisplayPosition(0),
	m_iPortraitIndex(-1),
	m_bTeamShare(false),
	m_bWater(false),
	m_bRiver(false),
	m_bFreshWater(false),
#if defined(MOD_MORE_NATURAL_WONDER)
	m_bImmueVolcanoDamage(false),
#endif
#if defined(MOD_API_EXTENSIONS)
	m_bAddsFreshWater(false),
	m_bPurchaseOnly(false),
	m_bHumanOnly(false),
#endif

	m_bMoveAfterCreated(false),

#if defined(MOD_ROG_CORE)
	m_piGreatWorkYieldChange(NULL),

	m_iExtraDamageHealPercent(0),
	m_iExtraDamageHeal(0),
	m_iBombardRange(0),
	m_bBombardIndirect(0),
	m_iRangedStrikeModifier(0),
	m_iPopulationChange(0),
	m_iMinorCivFriendship(0),
	m_iLiberatedInfluence(0),
	m_iExtraUnitPlayerInstances(0),
	m_iResetDamageValue(0),
	m_iReduceDamageValue(0),

	m_iGlobalCityStrengthMod(0),
	m_iGlobalRangedStrikeModifier(0),
	m_iResearchTotalCostModifier(0),
	m_iResearchTotalCostModifierGoldenAge(0),
	m_iWaterTileDamage(0),
	m_iWaterTileMovementReduce(0),
	m_iWaterTileTurnDamage(0),
	m_iLandTileDamage(0),
	m_iLandTileMovementReduce(0),
	m_iLandTileTurnDamage(0),

	m_iWaterTileDamageGlobal(0),
	m_iWaterTileMovementReduceGlobal(0),
	m_iWaterTileTurnDamageGlobal(0),
	m_iLandTileDamageGlobal(0),
	m_iLandTileMovementReduceGlobal(0),
	m_iLandTileTurnDamageGlobal(0),
#endif

	m_iNukeInterceptionChance(0),
	m_iExtraAttacks(0),

#if defined(MOD_GLOBAL_BUILDING_INSTANT_YIELD)
	m_piInstantYield(NULL),
	m_iInstantYieldCount(0),
#endif
	m_piYieldFromInternal(NULL),
	m_piYieldFromProcessModifier(NULL),
	m_piYieldFromProcessModifierGlobal(NULL),

#if defined(MOD_ROG_CORE)
	m_piResourceQuantityFromPOP(NULL),
	m_piYieldPerFriend(NULL),
	m_piYieldPerAlly(NULL),
	m_ppiResourceYieldChangeGlobal(),
	m_ppaiImprovementYieldChange(NULL),
	m_ppaiImprovementYieldChangeGlobal(NULL),
	m_ppiFeatureYieldChangesGlobal(NULL),
	m_ppiTerrainYieldChangesGlobal(NULL),
	m_ppaiYieldPerXTerrain(NULL),
	m_ppaiYieldPerXFeature(NULL),

	m_ppaiSpecialistYieldChangeLocal(NULL),
	m_piYieldPerEspionageSpy(NULL),
	m_piYieldChangeWorldWonder(NULL),
	m_piYieldChangeWorldWonderGlobal(NULL),

	m_ppiBuildingClassYieldModifiers(NULL),
	m_ppiBuildingClassLocalYieldChanges(NULL),
	m_piYieldChangePerPopInEmpire(),
#endif


	m_bMountain(false),
	m_bHill(false),
	m_bFlat(false),
	m_bFoundsReligion(false),
	m_bIsReligious(false),
	m_bBorderObstacle(false),
	m_bPlayerBorderObstacle(false),
	m_bCapital(false),
	m_bGoldenAge(false),
	m_bMapCentering(false),
	m_bNeverCapture(false),
	m_bNukeImmune(false),
	m_bExtraAttackOnKill(false),
	m_bIsForbiddenForeignSpy(false),
	m_bIsForbiddenForeignSpyGlobal(false),
	m_bExtraLuxuries(false),
	m_bDiplomaticVoting(false),
	m_bAllowsWaterRoutes(false),
	m_bCityWall(false),
	m_bUnlockedByBelief(false),
	m_bUnlockedByLeague(false),
	m_bRequiresHolyCity(false),
	m_bAffectSpiesNow(false),
	m_bEspionage(false),
	m_bAllowsFoodTradeRoutes(false),
	m_bAllowsProductionTradeRoutes(false),
	m_bNullifyInfluenceModifier(false),
	m_piResourceQuantityRequirements(NULL),
	m_piResourceQuantity(NULL),
	m_piResourceCultureChanges(NULL),
	m_piResourceFaithChanges(NULL),
	m_piProductionTraits(NULL),
	m_piSeaPlotYieldChange(NULL),
	m_piRiverPlotYieldChange(NULL),
	m_piRiverPlotYieldChangeGlobal(NULL),
	m_piLakePlotYieldChange(NULL),
	m_piSeaResourceYieldChange(NULL),
	m_piYieldChange(NULL),
	m_piYieldChangePerEra(NULL),
	m_piYieldModifierChangePerEra(NULL),
	m_piCityStateTradeRouteYieldModifier(NULL),
	m_piCityStateTradeRouteYieldModifierGlobal(NULL),
	m_piYieldChangePerPop(NULL),
	m_piYieldChangePerReligion(NULL),
	m_piYieldModifier(NULL),
	m_piYieldMultiplier(NULL),
	m_piAreaYieldModifier(NULL),
	m_piGlobalYieldModifier(NULL),
	m_piTechEnhancedYieldChange(NULL),
	m_piUnitCombatFreeExperience(NULL),
	m_piUnitCombatProductionModifiers(NULL),
	m_piDomainFreeExperience(NULL),
	m_piDomainFreeExperiencePerGreatWork(NULL),
	m_piDomainFreeExperiencesPerPop(NULL),
	m_piDomainFreeExperiencesPerPopGlobal(NULL),
	m_piDomainFreeExperiencesPerTurn(NULL),
	m_piDomainFreeExperiencesPerTurnGlobal(NULL),
	m_piDomainEnemyCombatModifier(NULL),
	m_piDomainEnemyCombatModifierGlobal(NULL),
	m_piDomainFriendsCombatModifierLocal(NULL),

#if defined(MOD_ROG_CORE)
	m_piYieldFromConstruction(NULL),
	m_piYieldFromUnitProduction(NULL),
	m_piYieldFromBirth(NULL),
	m_piYieldFromBorderGrowth(NULL),

	m_piYieldFromPillage(NULL),
	m_piYieldFromPillageGlobal(NULL),
	m_piYieldFromPillageGlobalPlayer(NULL),

	m_piYieldModifierFromWonder(NULL),
	m_piDomainFreeExperiencePerGreatWorkGlobal(NULL),
	m_piDomainFreeExperienceGlobal(),
	m_piUnitTypePrmoteHealGlobal(),
	m_paiSpecificGreatPersonRateModifier(NULL),
#endif

#if defined(MOD_NUCLEAR_WINTER_FOR_SP)
	m_bNoNuclearWinterLocal(false),
#endif

#if defined(MOD_TROOPS_AND_CROPS_FOR_SP)
	m_piDomainTroops(NULL),
	m_iNumCrops(0),
	m_iNumArmee(0),
	m_bEnableCrops(0),
	m_bEnableArmee(0),
#endif


	m_piDomainProductionModifier(NULL),
	m_piPrereqNumOfBuildingClass(NULL),
	m_piFlavorValue(NULL),
	m_piLocalResourceAnds(NULL),
	m_piLocalResourceOrs(NULL),

	m_piEmpireResourceAnds(NULL),
	m_piEmpireResourceOrs(NULL),
    m_piLocalFeatureOrs(NULL),
	m_piLocalFeatureAnds(NULL),
	m_piLocalPlotAnds(NULL),

	m_paiHurryModifier(NULL),
	m_paiHurryModifierLocal(NULL),
#if defined(MOD_BUILDING_NEW_EFFECT_FOR_SP)
	m_iCityDefenseModifierGlobal(0),
	m_iUnitMaxExperienceLocal(0),
	m_iExtraSellRefund(0),
	m_iExtraSellRefundModifierPerEra(0),
	m_iMinNumReligions(0),
	m_iLandmarksTourismPercentGlobal(0),
	m_iGreatWorksTourismModifierGlobal(0),
	m_iTradeRouteSeaGoldBonusGlobal(0),
	m_iTradeRouteLandGoldBonusGlobal(0),
	m_bAnyWater(false),
	m_bRiverOrCoastal(false),
#endif
	m_bArtInfoEraVariation(false),
	m_bArtInfoCulturalVariation(false),
	m_bArtInfoRandomVariation(false),
	m_ppaiResourceYieldChange(NULL),
	m_ppaiFeatureYieldChange(NULL),
	m_ppaiTerrainYieldModifier(NULL),
	m_ppaiSpecialistYieldChange(NULL),
	m_ppaiImprovementYieldModifier(NULL),
	m_ppaiSpecialistYieldModifier(NULL),
	m_ppaiSpecialistYieldModifierGlobal(NULL),
	m_ppaiFeatureYieldModifier(NULL),
	m_ppaiResourceYieldModifier(NULL),
	m_ppaiTerrainYieldChange(NULL),
#if defined(MOD_API_UNIFIED_YIELDS) && defined(MOD_API_PLOT_YIELDS)
	m_ppaiPlotYieldChange(NULL),
#endif
	m_ppiBuildingClassYieldChanges(NULL),
	m_paiBuildingClassHappiness(NULL),
	m_paYieldFromYieldGlobal(NULL),
	m_paThemingBonusInfo(NULL),

#if defined(MOD_BUILDING_IMPROVEMENT_RESOURCES)
	m_piiResourceFromImprovement(),
#endif

	m_iNumThemingBonuses(0),
#ifdef MOD_BUILDINGS_YIELD_FROM_OTHER_YIELD
	m_bHasYieldFromOtherYield(false),
#endif
	m_iNumFreeUnit(0),
	m_iNumFreeUnitTotal(0),
	m_pFreeUnits(nullptr),

	m_bCapitalOnly(false),
	m_bOriginalCapitalOnly(false)

{
#ifdef MOD_API_BUILDING_ENABLE_PURCHASE_UNITS
	for (int i = 0; i < NUM_YIELD_TYPES; i++) {
		m_iNumAllowPurchaseUnits[i] = 0;
		m_piAllowPurchaseUnits[i] = nullptr;
	}
#endif
}

/// Destructor
CvBuildingEntry::~CvBuildingEntry(void)
{
	SAFE_DELETE_ARRAY(m_piResourceQuantityRequirements);
	SAFE_DELETE_ARRAY(m_piResourceQuantity);
	SAFE_DELETE_ARRAY(m_piResourceCultureChanges);
	SAFE_DELETE_ARRAY(m_piResourceFaithChanges);
	SAFE_DELETE_ARRAY(m_piProductionTraits);
	SAFE_DELETE_ARRAY(m_piSeaPlotYieldChange);
	SAFE_DELETE_ARRAY(m_piRiverPlotYieldChange);
	SAFE_DELETE_ARRAY(m_piRiverPlotYieldChangeGlobal);
	SAFE_DELETE_ARRAY(m_piLakePlotYieldChange);
	SAFE_DELETE_ARRAY(m_piSeaResourceYieldChange);
	SAFE_DELETE_ARRAY(m_piYieldChange);
	SAFE_DELETE_ARRAY(m_piYieldChangePerEra);
	SAFE_DELETE_ARRAY(m_piYieldModifierChangePerEra);
	SAFE_DELETE_ARRAY(m_piCityStateTradeRouteYieldModifier);
	SAFE_DELETE_ARRAY(m_piCityStateTradeRouteYieldModifierGlobal);
	SAFE_DELETE_ARRAY(m_piYieldChangePerPop);
	SAFE_DELETE_ARRAY(m_piYieldChangePerReligion);
	SAFE_DELETE_ARRAY(m_piYieldModifier);
	SAFE_DELETE_ARRAY(m_piYieldMultiplier);
	SAFE_DELETE_ARRAY(m_piAreaYieldModifier);
	SAFE_DELETE_ARRAY(m_piGlobalYieldModifier);
	SAFE_DELETE_ARRAY(m_piTechEnhancedYieldChange);
	SAFE_DELETE_ARRAY(m_piUnitCombatFreeExperience);
	SAFE_DELETE_ARRAY(m_piUnitCombatProductionModifiers);
	SAFE_DELETE_ARRAY(m_piDomainFreeExperience);
	SAFE_DELETE_ARRAY(m_piDomainFreeExperiencePerGreatWork);
	SAFE_DELETE_ARRAY(m_piDomainFreeExperiencesPerPop);
	SAFE_DELETE_ARRAY(m_piDomainFreeExperiencesPerPopGlobal);
	SAFE_DELETE_ARRAY(m_piDomainFreeExperiencesPerTurn);
	SAFE_DELETE_ARRAY(m_piDomainFreeExperiencesPerTurnGlobal);
	SAFE_DELETE_ARRAY(m_piDomainEnemyCombatModifier);
	SAFE_DELETE_ARRAY(m_piDomainEnemyCombatModifierGlobal);
	SAFE_DELETE_ARRAY(m_piDomainFriendsCombatModifierLocal);
#if defined(MOD_ROG_CORE)
	SAFE_DELETE_ARRAY(m_piYieldFromConstruction);
	SAFE_DELETE_ARRAY(m_piYieldFromUnitProduction);
	SAFE_DELETE_ARRAY(m_piYieldFromBirth);
	SAFE_DELETE_ARRAY(m_piYieldFromBorderGrowth);
	SAFE_DELETE_ARRAY(m_piYieldFromPillage);
	SAFE_DELETE_ARRAY(m_piYieldFromPillageGlobal);
	SAFE_DELETE_ARRAY(m_piYieldFromPillageGlobalPlayer);
	SAFE_DELETE_ARRAY(m_piYieldModifierFromWonder);
	SAFE_DELETE_ARRAY(m_piDomainFreeExperiencePerGreatWorkGlobal);
	m_piDomainFreeExperienceGlobal.clear();
	m_piUnitTypePrmoteHealGlobal.clear();
#endif

#if defined(MOD_TROOPS_AND_CROPS_FOR_SP)
	SAFE_DELETE_ARRAY(m_piDomainTroops);
#endif

	SAFE_DELETE_ARRAY(m_piDomainProductionModifier);
	SAFE_DELETE_ARRAY(m_piPrereqNumOfBuildingClass);
	SAFE_DELETE_ARRAY(m_piFlavorValue);

	SAFE_DELETE_ARRAY(m_paiHurryModifier);
	SAFE_DELETE_ARRAY(m_paiHurryModifierLocal);
	SAFE_DELETE_ARRAY(m_paiBuildingClassHappiness);
	SAFE_DELETE_ARRAY(m_paYieldFromYieldGlobal);
	SAFE_DELETE_ARRAY(m_paThemingBonusInfo);

#if defined(MOD_GLOBAL_BUILDING_INSTANT_YIELD)
	SAFE_DELETE_ARRAY(m_piInstantYield);
#endif
	SAFE_DELETE_ARRAY(m_piYieldFromInternal);
	SAFE_DELETE_ARRAY(m_piYieldFromProcessModifier);
	SAFE_DELETE_ARRAY(m_piYieldFromProcessModifierGlobal);

#if defined(MOD_ROG_CORE)
	SAFE_DELETE_ARRAY(m_piResourceQuantityFromPOP);
	SAFE_DELETE_ARRAY(m_piYieldPerFriend);
	SAFE_DELETE_ARRAY(m_piYieldPerAlly);
	SAFE_DELETE_ARRAY(m_piGreatWorkYieldChange);
	SAFE_DELETE_ARRAY(m_piYieldPerEspionageSpy);
	SAFE_DELETE_ARRAY(m_piYieldChangeWorldWonder);
	SAFE_DELETE_ARRAY(m_piYieldChangeWorldWonderGlobal);
	SAFE_DELETE_ARRAY(m_paiSpecificGreatPersonRateModifier);
#endif

#if defined(MOD_BUILDING_IMPROVEMENT_RESOURCES)
	m_piiResourceFromImprovement.clear();
#endif

	CvDatabaseUtility::SafeDelete2DArray(m_ppaiResourceYieldChange);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiFeatureYieldChange);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiTerrainYieldModifier);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiSpecialistYieldChange);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiImprovementYieldModifier);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiSpecialistYieldModifier);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiSpecialistYieldModifierGlobal);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiFeatureYieldModifier);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiResourceYieldModifier);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiTerrainYieldChange);

#if defined(MOD_ROG_CORE)
	m_piYieldChangePerPopInEmpire.clear();
	m_ppiResourceYieldChangeGlobal.clear();
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiImprovementYieldChange);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiImprovementYieldChangeGlobal);
	CvDatabaseUtility::SafeDelete2DArray(m_ppiTerrainYieldChangesGlobal);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiImprovementYieldChangeGlobal);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiYieldPerXTerrain);
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiYieldPerXFeature);

	CvDatabaseUtility::SafeDelete2DArray(m_ppaiSpecialistYieldChangeLocal);
	CvDatabaseUtility::SafeDelete2DArray(m_ppiBuildingClassYieldModifiers);
	CvDatabaseUtility::SafeDelete2DArray(m_ppiBuildingClassLocalYieldChanges);
#endif


#if defined(MOD_API_UNIFIED_YIELDS) && defined(MOD_API_PLOT_YIELDS)
	CvDatabaseUtility::SafeDelete2DArray(m_ppaiPlotYieldChange);
#endif
	CvDatabaseUtility::SafeDelete2DArray(m_ppiBuildingClassYieldChanges);
	if(m_pFreeUnits)
	{
		delete m_pFreeUnits;
	}


#ifdef MOD_API_BUILDING_ENABLE_PURCHASE_UNITS
	if (MOD_API_BUILDING_ENABLE_PURCHASE_UNITS) {
		for (int i = 0; i < NUM_YIELD_TYPES; i++) {
			if(m_piAllowPurchaseUnits[i]) delete[] m_piAllowPurchaseUnits[i];
		}
	}
#endif

}

/// Read from XML file
bool CvBuildingEntry::CacheResults(Database::Results& kResults, CvDatabaseUtility& kUtility)
{
	if(!CvBaseInfo::CacheResults(kResults, kUtility))
		return false;

	//Basic Properties
	m_iGoldMaintenance = kResults.GetInt("GoldMaintenance");
	m_bTeamShare = kResults.GetBool("TeamShare");
	m_bWater = kResults.GetBool("Water");
	m_bRiver = kResults.GetBool("River");
	m_bFreshWater = kResults.GetBool("FreshWater");
#if defined(MOD_MORE_NATURAL_WONDER)
	m_bImmueVolcanoDamage = kResults.GetBool("ImmueVolcanoDamage"); 
#endif
#if defined(MOD_API_EXTENSIONS)
	if (MOD_API_EXTENSIONS) {
		m_bAddsFreshWater = kResults.GetBool("AddsFreshWater");
		m_bPurchaseOnly = kResults.GetBool("PurchaseOnly");
		m_bHumanOnly = kResults.GetBool("HumanOnly");
	}
#endif

	m_bMoveAfterCreated = kResults.GetBool("MoveAfterCreated");

#if defined(MOD_ROG_CORE)
	m_iExtraDamageHealPercent = kResults.GetInt("ExtraDamageHealPercent");
	m_iExtraDamageHeal = kResults.GetInt("ExtraDamageHeal");
	m_iBombardRange = kResults.GetInt("BombardRange");
	m_bBombardIndirect = kResults.GetInt("BombardIndirect");
	m_iRangedStrikeModifier = kResults.GetInt("RangedStrikeModifier");
	m_iPopulationChange = kResults.GetInt("PopulationChange");
	m_iMinorCivFriendship = kResults.GetInt("MinorCivFriendship");
	m_iLiberatedInfluence = kResults.GetInt("LiberatedInfluence");
	m_iExtraUnitPlayerInstances = kResults.GetInt("ExtraUnitPlayerInstances");
	m_iResetDamageValue = kResults.GetInt("ResetDamageValue");
	m_iReduceDamageValue = kResults.GetInt("ReduceDamageValue");

	m_iGlobalCityStrengthMod = kResults.GetInt("GlobalCityStrengthMod");
	m_iGlobalRangedStrikeModifier = kResults.GetInt("GlobalRangedStrikeModifier");
	m_iResearchTotalCostModifier = kResults.GetInt("ResearchTotalCostModifier");
	m_iResearchTotalCostModifierGoldenAge = kResults.GetInt("ResearchTotalCostModifierGoldenAge");
	m_iWaterTileDamage = kResults.GetInt("WaterTileDamage");
	m_iWaterTileMovementReduce = kResults.GetInt("WaterTileMovementReduce");
	m_iWaterTileTurnDamage = kResults.GetInt("WaterTileTurnDamage");
	m_iLandTileDamage = kResults.GetInt("LandTileDamage");
	m_iLandTileMovementReduce = kResults.GetInt("LandTileMovementReduce");
	m_iLandTileTurnDamage = kResults.GetInt("LandTileTurnDamage");

	m_iWaterTileDamageGlobal = kResults.GetInt("WaterTileDamageGlobal");
	m_iWaterTileMovementReduceGlobal = kResults.GetInt("WaterTileMovementReduceGlobal");
	m_iWaterTileTurnDamageGlobal = kResults.GetInt("WaterTileTurnDamageGlobal");
	m_iLandTileDamageGlobal = kResults.GetInt("LandTileDamageGlobal");
	m_iLandTileMovementReduceGlobal = kResults.GetInt("LandTileMovementReduceGlobal");
	m_iLandTileTurnDamageGlobal = kResults.GetInt("LandTileTurnDamageGlobal");
#endif

	m_iNukeInterceptionChance = kResults.GetInt("NukeInterceptionChance");
	m_iExtraAttacks = kResults.GetInt("ExtraAttacks");

#if defined(MOD_BUILDING_NEW_EFFECT_FOR_SP)
	m_iCityDefenseModifierGlobal = kResults.GetInt("CityDefenseModifierGlobal");
	m_iUnitMaxExperienceLocal = kResults.GetInt("UnitMaxExperienceLocal");
	m_iExtraSellRefund = kResults.GetInt("ExtraSellRefund");
	m_iExtraSellRefundModifierPerEra = kResults.GetInt("ExtraSellRefundModifierPerEra");
	m_iMinNumReligions = kResults.GetInt("MinNumReligions");
	m_iLandmarksTourismPercentGlobal = kResults.GetInt("LandmarksTourismPercentGlobal");
	m_iGreatWorksTourismModifierGlobal = kResults.GetInt("GreatWorksTourismModifierGlobal");
	m_iTradeRouteSeaGoldBonusGlobal = kResults.GetInt("TradeRouteSeaGoldBonusGlobal");
	m_iTradeRouteLandGoldBonusGlobal = kResults.GetInt("TradeRouteLandGoldBonusGlobal");
	m_bAnyWater = kResults.GetBool("AnyWater");
	m_bRiverOrCoastal = kResults.GetBool("RiverOrCoastal");
#endif
	m_bMountain = kResults.GetBool("Mountain");
	m_bHill = kResults.GetBool("Hill");
	m_bFlat = kResults.GetBool("Flat");
	m_bFoundsReligion = kResults.GetBool("FoundsReligion");
	m_bIsReligious = kResults.GetBool("IsReligious");
	m_bBorderObstacle = kResults.GetBool("BorderObstacle");
	m_bPlayerBorderObstacle = kResults.GetBool("PlayerBorderObstacle");
	m_bCapital = kResults.GetBool("Capital");
	m_bGoldenAge = kResults.GetBool("GoldenAge");
	m_bMapCentering = kResults.GetBool("MapCentering");
	m_bNeverCapture = kResults.GetBool("NeverCapture");
	m_bNukeImmune = kResults.GetBool("NukeImmune");
	m_bExtraAttackOnKill = kResults.GetBool("CityCollateralDamage");
	m_bIsForbiddenForeignSpy = kResults.GetBool("ForbiddenForeignSpy");
	m_bIsForbiddenForeignSpyGlobal = kResults.GetBool("ForbiddenForeignSpyGlobal");
	m_bCityWall = kResults.GetBool("CityWall");
	m_bExtraLuxuries = kResults.GetBool("ExtraLuxuries");
	m_bDiplomaticVoting = kResults.GetBool("DiplomaticVoting");
	m_bAllowsWaterRoutes = kResults.GetBool("AllowsWaterRoutes");
	m_iProductionCost = kResults.GetInt("Cost");
	m_iFaithCost = kResults.GetInt("FaithCost");
	m_iLeagueCost = kResults.GetInt("LeagueCost");
	m_bUnlockedByBelief = kResults.GetBool("UnlockedByBelief");
	m_bUnlockedByLeague = kResults.GetBool("UnlockedByLeague");
	m_bRequiresHolyCity = kResults.GetBool("HolyCity");
	m_bAffectSpiesNow = kResults.GetBool("AffectSpiesNow");
	m_bEspionage = kResults.GetBool("Espionage");
	m_bAllowsFoodTradeRoutes = kResults.GetBool("AllowsFoodTradeRoutes");
	m_bAllowsProductionTradeRoutes = kResults.GetBool("AllowsProductionTradeRoutes");
	m_bNullifyInfluenceModifier = kResults.GetBool("NullifyInfluenceModifier");
	m_iNumCityCostMod = kResults.GetInt("NumCityCostMod");
	m_iHurryCostModifier = kResults.GetInt("HurryCostModifier");
	m_iMinAreaSize = kResults.GetInt("MinAreaSize");
	m_iConquestProbability = kResults.GetInt("ConquestProb");
	m_iNumCitiesPrereq = kResults.GetInt("CitiesPrereq");
	m_iUnitLevelPrereq = kResults.GetInt("LevelPrereq");
	m_iCultureRateModifier = kResults.GetInt("CultureRateModifier");
	m_iGlobalCultureRateModifier = kResults.GetInt("GlobalCultureRateModifier");
	m_iGreatPeopleRateModifier = kResults.GetInt("GreatPeopleRateModifier");
	m_iGlobalGreatPeopleRateModifier = kResults.GetInt("GlobalGreatPeopleRateModifier");
	m_iGreatGeneralRateModifier = kResults.GetInt("GreatGeneralRateModifier");
	m_iGreatPersonExpendGold = kResults.GetInt("GreatPersonExpendGold");
	m_iUnitUpgradeCostMod = kResults.GetInt("UnitUpgradeCostMod");
	m_iGoldenAgeModifier = kResults.GetInt("GoldenAgeModifier");
	m_iFreeExperience = kResults.GetInt("Experience");
	m_iGlobalFreeExperience = kResults.GetInt("GlobalExperience");
	m_iFoodKept = kResults.GetInt("FoodKept");
	m_bAirlift = kResults.GetBool("Airlift");
	m_iAirModifier = kResults.GetInt("AirModifier");
	m_iNukeModifier = kResults.GetInt("NukeModifier");
	m_iNukeExplosionRand = kResults.GetInt("NukeExplosionRand");
	m_iHealRateChange = kResults.GetInt("HealRateChange");
	m_iHappiness = kResults.GetInt("Happiness");
	m_iUnmoddedHappiness = kResults.GetInt("UnmoddedHappiness");
	m_iUnhappinessModifier = kResults.GetInt("UnhappinessModifier");
	m_iHappinessPerCity = kResults.GetInt("HappinessPerCity");
	m_iHappinessPerXPolicies = kResults.GetInt("HappinessPerXPolicies");
	m_iCityCountUnhappinessMod = kResults.GetInt("CityCountUnhappinessMod");
	m_bNoOccupiedUnhappiness = kResults.GetBool("NoOccupiedUnhappiness");
	m_bNotNeedOccupied = kResults.GetBool("NotNeedOccupied");
	m_iWorkerSpeedModifier = kResults.GetInt("WorkerSpeedModifier");
	m_iMilitaryProductionModifier = kResults.GetInt("MilitaryProductionModifier");
	m_iSpaceProductionModifier = kResults.GetInt("SpaceProductionModifier");
	m_iGlobalSpaceProductionModifier = kResults.GetInt("GlobalSpaceProductionModifier");
	m_iBuildingProductionModifier = kResults.GetInt("BuildingProductionModifier");
	m_iWonderProductionModifier = kResults.GetInt("WonderProductionModifier");
	m_iCityConnectionTradeRouteModifier = kResults.GetInt("CityConnectionTradeRouteModifier");
	m_iCapturePlunderModifier = kResults.GetInt("CapturePlunderModifier");
	m_iPolicyCostModifier = kResults.GetInt("PolicyCostModifier");
	m_iPlotCultureCostModifier = kResults.GetInt("PlotCultureCostModifier");
	m_iGlobalPlotCultureCostModifier = kResults.GetInt("GlobalPlotCultureCostModifier");
	m_iPlotBuyCostModifier = kResults.GetInt("PlotBuyCostModifier");
	m_iGlobalPlotBuyCostModifier = kResults.GetInt("GlobalPlotBuyCostModifier");
#if defined(MOD_BUILDINGS_CITY_WORKING)
	m_iCityWorkingChange = kResults.GetInt("CityWorkingChange");
	m_iGlobalCityWorkingChange = kResults.GetInt("GlobalCityWorkingChange");
#endif
#if defined(MOD_BUILDINGS_CITY_AUTOMATON_WORKERS)
	m_iCityAutomatonWorkersChange = kResults.GetInt("CityAutomatonWorkersChange");
	m_iGlobalCityAutomatonWorkersChange = kResults.GetInt("GlobalCityAutomatonWorkersChange");
#endif
	m_iGlobalPopulationChange = kResults.GetInt("GlobalPopulationChange");
	m_iTechShare = kResults.GetInt("TechShare");
	m_iFreeTechs = kResults.GetInt("FreeTechs");
	m_iFreePolicies = kResults.GetInt("FreePolicies");
	m_iFreeGreatPeople = kResults.GetInt("FreeGreatPeople");
	m_iMedianTechPercentChange = kResults.GetInt("MedianTechPercentChange");
	m_iGold = kResults.GetInt("Gold");
	m_bNearbyMountainRequired = kResults.GetInt("NearbyMountainRequired");
	m_bAllowsRangeStrike = kResults.GetInt("AllowsRangeStrike");
	m_iDefenseModifier = kResults.GetInt("Defense");
	m_iGlobalDefenseModifier = kResults.GetInt("GlobalDefenseMod");
	m_iExtraCityHitPoints = kResults.GetInt("ExtraCityHitPoints");
	m_iMinorFriendshipChange = kResults.GetInt("MinorFriendshipChange");
	m_iMinorFriendshipAnchorChange = kResults.GetInt("MinorFriendshipAnchorChange");
	m_iMinorQuestFriendshipMod = kResults.GetInt("MinorQuestFriendshipMod");
	m_iVictoryPoints = kResults.GetInt("VictoryPoints");
	m_iExtraMissionarySpreads = kResults.GetInt("ExtraMissionarySpreads");
	m_iReligiousPressureModifier = kResults.GetInt("ReligiousPressureModifier");
	m_iEspionageModifier = kResults.GetInt("EspionageModifier");
	m_iGlobalEspionageModifier = kResults.GetInt("GlobalEspionageModifier");
	m_iGlobalEspionageSpeedModifier = kResults.GetInt("GlobalEspionageSpeedModifier");
	m_iExtraSpies = kResults.GetInt("ExtraSpies");
	m_iSpyRankChange = kResults.GetInt("SpyRankChange");
	m_iTradeRouteRecipientBonus = kResults.GetInt("TradeRouteRecipientBonus");
	m_iTradeRouteTargetBonus = kResults.GetInt("TradeRouteTargetBonus");
	m_iNumTradeRouteBonus = kResults.GetInt("NumTradeRouteBonus");
	m_iTradeRouteSeaDistanceModifier = kResults.GetInt("TradeRouteSeaDistanceModifier");
	m_iTradeRouteSeaGoldBonus = kResults.GetInt("TradeRouteSeaGoldBonus");
	m_iTradeRouteLandDistanceModifier = kResults.GetInt("TradeRouteLandDistanceModifier");
	m_iTradeRouteLandGoldBonus = kResults.GetInt("TradeRouteLandGoldBonus");
#ifdef MOD_BUILDINGS_GOLDEN_AGE_EXTEND
	m_iGoldenAgeUnitCombatModifier = kResults.GetInt("GoldenAgeUnitCombatModifier");
	m_iGoldenAgeMeterMod = kResults.GetInt("GoldenAgeMeterMod");
#endif
#if defined(MOD_RELIGION_CONVERSION_MODIFIERS)
	m_iConversionModifier = kResults.GetInt("ConversionModifier");
	m_iGlobalConversionModifier = kResults.GetInt("GlobalConversionModifier");
#endif
	m_iInstantSpyRankChange = kResults.GetInt("InstantSpyRankChange");
	m_iLandmarksTourismPercent = kResults.GetInt("LandmarksTourismPercent");
	m_iInstantMilitaryIncrease = kResults.GetInt("InstantMilitaryIncrease");
	m_iGreatWorksTourismModifier = kResults.GetInt("GreatWorksTourismModifier");
	m_iXBuiltTriggersIdeologyChoice = kResults.GetInt("XBuiltTriggersIdeologyChoice");
	m_iGreatScientistBeakerModifier = kResults.GetInt("GreatScientistBeakerModifier");
	m_iExtraLeagueVotes = kResults.GetInt("ExtraLeagueVotes");
	m_iPreferredDisplayPosition = kResults.GetInt("DisplayPosition");
	m_iPortraitIndex = kResults.GetInt("PortraitIndex");

#if defined(MOD_NUCLEAR_WINTER_FOR_SP)
	m_bNoNuclearWinterLocal = kResults.GetBool("NoNuclearWinterLocal");
#endif

#if defined(MOD_TROOPS_AND_CROPS_FOR_SP)
	m_iNumCrops = kResults.GetInt("NumCrops");
	m_iNumArmee = kResults.GetInt("NumArmee");
	m_bEnableCrops = kResults.GetBool("EnableCrops");
	m_bEnableArmee = kResults.GetBool("EnableArmee");
#endif

	m_bArtInfoCulturalVariation = kResults.GetBool("ArtInfoCulturalVariation");
	m_bArtInfoEraVariation = kResults.GetBool("ArtInfoEraVariation");
	m_bArtInfoRandomVariation = kResults.GetBool("ArtInfoRandomVariation");

#ifdef MOD_PROMOTION_CITY_DESTROYER
	m_iSiegeKillCitizensModifier = kResults.GetInt("SiegeKillCitizensModifier");
#endif

#if defined(MOD_INTERNATIONAL_IMMIGRATION_FOR_SP)
	m_bCanAllScaleImmigrantIn = kResults.GetBool("EnableAlwaysImmigrantIn");
#endif

#ifdef MOD_GLOBAL_CORRUPTION
	m_iCorruptionScoreChange = kResults.GetInt("CorruptionScoreChange");
	m_iCorruptionLevelChange = kResults.GetInt("CorruptionLevelChange");
	m_iCorruptionPolicyCostModifier = kResults.GetInt("CorruptionPolicyCostModifier");
	m_iMinCorruptionLevelNeeded = kResults.GetInt("MinCorruptionLevelNeeded");
	m_iMaxCorruptionLevelNeeded = kResults.GetInt("MaxCorruptionLevelNeeded");
#endif

	m_iGlobalProductionNeededUnitModifier = kResults.GetInt("GlobalProductionNeededUnitModifier");
	m_iGlobalProductionNeededBuildingModifier = kResults.GetInt("GlobalProductionNeededBuildingModifier");
	m_iGlobalProductionNeededProjectModifier = kResults.GetInt("GlobalProductionNeededProjectModifier");
	m_iGlobalProductionNeededUnitMax = kResults.GetInt("GlobalProductionNeededUnitMax");
	m_iGlobalProductionNeededBuildingMax = kResults.GetInt("GlobalProductionNeededBuildingMax");
	m_iGlobalProductionNeededProjectMax = kResults.GetInt("GlobalProductionNeededProjectMax");
	m_bDummyBuilding = kResults.GetBool("DummyBuilding");
	m_bNoPuppet = kResults.GetBool("NoPuppet");

	m_iInstantResearchFromFriendlyGreatScientist = kResults.GetInt("InstantResearchFromFriendlyGreatScientist");

	m_iGlobalGrowthFoodNeededModifier = kResults.GetInt("GlobalGrowthFoodNeededModifier");
	m_iSecondCapitalsExtraScore = kResults.GetInt("SecondCapitalsExtraScore");
	m_iFoodKeptFromPollution = kResults.GetInt("FoodKeptFromPollution");

	m_bCapitalOnly = kResults.GetBool("CapitalOnly");
	m_bOriginalCapitalOnly = kResults.GetBool("OriginalCapitalOnly");

	//References
	const char* szTextVal;
	szTextVal = kResults.GetText("BuildingClass");
	m_iBuildingClassType = GC.getInfoTypeForString(szTextVal, true);

	//This may need to be deferred to a routine that is called AFTER pre-fetch has been called for all infos.
	m_pkBuildingClassInfo = GC.getBuildingClassInfo(static_cast<BuildingClassTypes>(m_iBuildingClassType));
	CvAssertMsg(m_pkBuildingClassInfo, "Could not find BuildingClassInfo for BuildingType. Have BuildingClasses been prefetched yet?");

	szTextVal = kResults.GetText("ArtDefineTag");
	SetArtDefineTag(szTextVal);

	szTextVal = kResults.GetText("WonderSplashAudio");
	m_strWonderSplashAudio = szTextVal;

	szTextVal = kResults.GetText("ThemingBonusHelp");
	m_strThemingBonusHelp = szTextVal;

	szTextVal = kResults.GetText("NearbyTerrainRequired");
	m_iNearbyTerrainRequired = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("ProhibitedCityTerrain");
	m_iProhibitedCityTerrain = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("VictoryPrereq");
	m_iVictoryPrereq = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("FreeStartEra");
	m_iFreeStartEra = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("MaxStartEra");
	m_iMaxStartEra = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("ObsoleteTech");
	m_iObsoleteTech = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("EnhancedYieldTech");
	m_iEnhancedYieldTech = GC.getInfoTypeForString(szTextVal, true);

	m_iTechEnhancedTourism = kResults.GetInt("TechEnhancedTourism");

	szTextVal = kResults.GetText("FreeBuilding");
	m_iFreeBuildingClass = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("FreeBuildingThisCity");
	m_iFreeBuildingThisCity = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("FreePromotion");
	m_iFreePromotion = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("FreePromotion2");
	m_iFreePromotion2 = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("FreePromotion3");
	m_iFreePromotion3 = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("TrainedFreePromotion");
	m_iTrainedFreePromotion = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("FreePromotionRemoved");
	m_iFreePromotionRemoved = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("ReplacementBuildingClass");
	m_iReplacementBuildingClass= GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("PrereqTech");
	m_iPrereqAndTech = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("TechNoPrereqClasses");
	m_iTechNoPrereqClasses = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("PolicyBranchType");
	m_iPolicyBranchType = GC.getInfoTypeForString(szTextVal, true);

	szTextVal = kResults.GetText("PolicyNeededType");
	m_iPolicyNeededType = GC.getInfoTypeForString(szTextVal, true);

	m_bPuppetPurchaseOverride = kResults.GetBool("PuppetPurchaseOverride");
	m_bAllowsPuppetPurchase = kResults.GetBool("AllowsPuppetPurchase");

	szTextVal = kResults.GetText("SpecialistType");
	m_iSpecialistType = GC.getInfoTypeForString(szTextVal, true);
	m_iSpecialistCount = kResults.GetInt("SpecialistCount");
	m_iSpecialistExtraCulture = kResults.GetInt("SpecialistExtraCulture");
	m_iGreatPeopleRateChange= kResults.GetInt("GreatPeopleRateChange");

	szTextVal = kResults.GetText("GreatWorkSlotType");
	m_eGreatWorkSlotType = (GreatWorkSlotType)GC.getInfoTypeForString(szTextVal, true);
#if defined(MOD_GLOBAL_GREATWORK_YIELDTYPES)
	szTextVal = kResults.GetText("GreatWorkYieldType");
	m_eGreatWorkYieldType = (YieldTypes)GC.getInfoTypeForString(szTextVal, true);
#endif
	m_iGreatWorkCount = kResults.GetInt("GreatWorkCount");
	szTextVal = kResults.GetText("FreeGreatWork");
	m_eFreeGreatWork = (GreatWorkType)GC.getInfoTypeForString(szTextVal, true);

	//Arrays
	const char* szBuildingType = GetType();

	kUtility.SetFlavors(m_piFlavorValue, "Building_Flavors", "BuildingType", szBuildingType);
	
	kUtility.SetYields(m_piSeaPlotYieldChange, "Building_SeaPlotYieldChanges", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piRiverPlotYieldChange, "Building_RiverPlotYieldChanges", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piRiverPlotYieldChangeGlobal, "Building_RiverPlotYieldChangesGlobal", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piLakePlotYieldChange, "Building_LakePlotYieldChanges", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piSeaResourceYieldChange, "Building_SeaResourceYieldChanges", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldChange, "Building_YieldChanges", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldChangePerEra, "Building_YieldChangesPerEra", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldModifierChangePerEra, "Building_YieldModifiersChangesPerEra", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piCityStateTradeRouteYieldModifier, "Building_CityStateTradeRouteYieldModifiers", "BuildingType", szBuildingType);
	m_piCityStateTradeRouteYieldModifier[YIELD_PRODUCTION] += kResults.GetInt("CityStateTradeRouteProductionModifier");
	kUtility.SetYields(m_piCityStateTradeRouteYieldModifierGlobal, "Building_CityStateTradeRouteYieldModifiersGlobal", "BuildingType", szBuildingType);
	m_piCityStateTradeRouteYieldModifierGlobal[YIELD_PRODUCTION] += kResults.GetInt("CityStateTradeRouteProductionModifierGlobal");
	kUtility.SetYields(m_piYieldChangePerPop, "Building_YieldChangesPerPop", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldChangePerReligion, "Building_YieldChangesPerReligion", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldModifier, "Building_YieldModifiers", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldMultiplier, "Building_YieldMultiplier", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldFromInternal, "Building_YieldFromInternalTR", "BuildingType", szBuildingType);
#if defined(MOD_ROG_CORE)
	kUtility.SetYields(m_piYieldFromConstruction, "Building_YieldFromConstruction", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldFromUnitProduction, "Building_YieldFromUnitProduction", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldFromBirth, "Building_YieldFromBirth", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldFromBorderGrowth, "Building_YieldFromBorderGrowth", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldFromPillage, "Building_YieldFromPillage", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldFromPillageGlobal, "Building_YieldFromPillageGlobal", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldFromPillageGlobalPlayer, "Building_YieldFromPillageGlobalPlayer", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldModifierFromWonder, "Building_CityWithWorldWonderYieldModifierGlobal", "BuildingType", szBuildingType);
#endif

	kUtility.SetYields(m_piAreaYieldModifier, "Building_AreaYieldModifiers", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piGlobalYieldModifier, "Building_GlobalYieldModifiers", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piTechEnhancedYieldChange, "Building_TechEnhancedYieldChanges", "BuildingType", szBuildingType);

	kUtility.PopulateArrayByValue(m_piResourceQuantityRequirements, "Resources", "Building_ResourceQuantityRequirements", "ResourceType", "BuildingType", szBuildingType, "Cost");
	kUtility.PopulateArrayByValue(m_piResourceQuantity, "Resources", "Building_ResourceQuantity", "ResourceType", "BuildingType", szBuildingType, "Quantity");
	kUtility.PopulateArrayByValue(m_piResourceCultureChanges, "Resources", "Building_ResourceCultureChanges", "ResourceType", "BuildingType", szBuildingType, "CultureChange");
	kUtility.PopulateArrayByValue(m_piResourceFaithChanges, "Resources", "Building_ResourceFaithChanges", "ResourceType", "BuildingType", szBuildingType, "FaithChange");

	kUtility.PopulateArrayByValue(m_paiHurryModifier, "HurryInfos", "Building_HurryModifiers", "HurryType", "BuildingType", szBuildingType, "HurryCostModifier");
	kUtility.PopulateArrayByValue(m_paiHurryModifierLocal, "HurryInfos", "Building_HurryModifiersLocal", "HurryType", "BuildingType", szBuildingType, "HurryCostModifier");

	//kUtility.PopulateArrayByValue(m_piProductionTraits, "Traits", "Building_ProductionTraits", "TraitType", "BuildingType", szBuildingType, "Trait");

	kUtility.PopulateArrayByValue(m_piUnitCombatFreeExperience, "UnitCombatInfos", "Building_UnitCombatFreeExperiences", "UnitCombatType", "BuildingType", szBuildingType, "Experience");
	kUtility.PopulateArrayByValue(m_piUnitCombatProductionModifiers, "UnitCombatInfos", "Building_UnitCombatProductionModifiers", "UnitCombatType", "BuildingType", szBuildingType, "Modifier");
	kUtility.PopulateArrayByValue(m_piDomainFreeExperience, "Domains", "Building_DomainFreeExperiences", "DomainType", "BuildingType", szBuildingType, "Experience", 0, NUM_DOMAIN_TYPES);
	kUtility.PopulateArrayByValue(m_piDomainFreeExperiencePerGreatWork, "Domains", "Building_DomainFreeExperiencePerGreatWork", "DomainType", "BuildingType", szBuildingType, "Experience", 0, NUM_DOMAIN_TYPES);
	kUtility.PopulateArrayByValue(m_piDomainProductionModifier, "Domains", "Building_DomainProductionModifiers", "DomainType", "BuildingType", szBuildingType, "Modifier", 0, NUM_DOMAIN_TYPES);
	kUtility.PopulateArrayByValue(m_piDomainFreeExperiencesPerPop, "Domains", "Building_DomainFreeExperiencesPerPop", "DomainType", "BuildingType", szBuildingType, "Modifier", 0, NUM_DOMAIN_TYPES);
	kUtility.PopulateArrayByValue(m_piDomainFreeExperiencesPerPopGlobal, "Domains", "Building_DomainFreeExperiencesPerPopGlobal", "DomainType", "BuildingType", szBuildingType, "Modifier", 0, NUM_DOMAIN_TYPES);
	kUtility.PopulateArrayByValue(m_piDomainFreeExperiencesPerTurn, "Domains", "Building_DomainFreeExperiencesPerTurn", "DomainType", "BuildingType", szBuildingType, "Value", 0, NUM_DOMAIN_TYPES);
	kUtility.PopulateArrayByValue(m_piDomainFreeExperiencesPerTurnGlobal, "Domains", "Building_DomainFreeExperiencesPerTurnGlobal", "DomainType", "BuildingType", szBuildingType, "Value", 0, NUM_DOMAIN_TYPES);
	kUtility.PopulateArrayByValue(m_piDomainEnemyCombatModifier, "Domains", "Building_DomainEnemyCombatModifier", "DomainType", "BuildingType", szBuildingType, "Modifier", 0, NUM_DOMAIN_TYPES);
	kUtility.PopulateArrayByValue(m_piDomainEnemyCombatModifierGlobal, "Domains", "Building_DomainEnemyCombatModifierGlobal", "DomainType", "BuildingType", szBuildingType, "Modifier", 0, NUM_DOMAIN_TYPES);
	kUtility.PopulateArrayByValue(m_piDomainFriendsCombatModifierLocal, "Domains", "Building_DomainFriendsCombatModifierLocal", "DomainType", "BuildingType", szBuildingType, "Modifier", 0, NUM_DOMAIN_TYPES);


#if defined(MOD_ROG_CORE)
	kUtility.PopulateArrayByValue(m_piDomainFreeExperiencePerGreatWorkGlobal, "Domains", "Building_DomainFreeExperiencePerGreatWorkGlobal", "DomainType", "BuildingType", szBuildingType, "Experience", 0, NUM_DOMAIN_TYPES);
	kUtility.PopulateArrayByValue(m_paiSpecificGreatPersonRateModifier, "Specialists", "Building_SpecificGreatPersonRateModifier", "SpecialistType", "BuildingType", szBuildingType, "Modifier");
#endif

#if defined(MOD_TROOPS_AND_CROPS_FOR_SP)
	kUtility.PopulateArrayByValue(m_piDomainTroops, "Domains", "Building_DomainTroops", "DomainType", "BuildingType", szBuildingType, "NumTroop", 0, NUM_DOMAIN_TYPES);
#endif

	kUtility.PopulateArrayByValue(m_piPrereqNumOfBuildingClass, "BuildingClasses", "Building_PrereqBuildingClasses", "BuildingClassType", "BuildingType", szBuildingType, "NumBuildingNeeded");
	kUtility.PopulateArrayByExistence(m_setBuildingClassesNeededInCity, "BuildingClasses", "Building_ClassesNeededInCity", "BuildingClassType", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByExistence(m_setBuildingClassesNeededGlobal, "BuildingClasses", "Building_ClassesNeededGlobal", "BuildingClassType", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByExistence(m_setBuildingsNeededInCity, "Buildings", "Building_BuildingsNeededInCity", "PreBuildingType", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByExistence(m_setBuildingsNeededGlobal, "Buildings", "Building_BuildingsNeededGlobal", "PreBuildingType", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByValue(m_paiBuildingClassHappiness, "BuildingClasses", "Building_BuildingClassHappiness", "BuildingClassType", "BuildingType", szBuildingType, "Happiness");

	kUtility.PopulateArrayByExistence(m_piPrereqAndTechs, "Technologies", "Building_TechAndPrereqs", "TechType", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByExistence(m_piLocalResourceAnds, "Resources", "Building_LocalResourceAnds", "ResourceType", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByExistence(m_piLocalResourceOrs, "Resources", "Building_LocalResourceOrs", "ResourceType", "BuildingType", szBuildingType);

	kUtility.PopulateArrayByExistence(m_piEmpireResourceAnds, "Resources", "Building_EmpireResourceAnds", "ResourceType", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByExistence(m_piEmpireResourceOrs, "Resources", "Building_EmpireResourceOrs", "ResourceType", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByExistence(m_piLocalFeatureOrs, "Features", "Building_LocalFeatureOrs", "FeatureType", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByExistence(m_piLocalFeatureAnds, "Features", "Building_LocalFeatureAnds", "FeatureType", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByExistence(m_piLocalPlotAnds, "Plots", "Building_LocalPlotAnds", "PlotType", "BuildingType", szBuildingType);
	
	// Building Locked By Buildings
	// Read both table Building_LockedBuildingClasses and column MutuallyExclusiveGroup and expect to be more effective
	{
		std::string strKey("Building_LockedBuildingClasses");
		Database::Results* pResults = kUtility.GetResults(strKey);
		const char* szBuildingClass = kResults.GetText("BuildingClass");
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select t2.ID from Building_LockedBuildingClasses t1 inner join Buildings t2 on t1.BuildingType = t2.Type where t1.BuildingClassType = ?");
		}

		pResults->Bind(1, szBuildingClass);
		while(pResults->Step()) m_piLockedByBuildings.push_back(pResults->GetInt(0));
	}
	{
		std::string strKey("Buildings.MutuallyExclusiveGroup");
		Database::Results* pResults = kUtility.GetResults(strKey);
		int iGroup = kResults.GetInt("MutuallyExclusiveGroup");
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select ID from Buildings where MutuallyExclusiveGroup != -1 and MutuallyExclusiveGroup = ? and Type != ?");
		}

		pResults->Bind(1, iGroup);
		pResults->Bind(2, szBuildingType);
		while(pResults->Step()) m_piLockedByBuildings.push_back(pResults->GetInt(0));
	}
#if defined(MOD_GLOBAL_BUILDING_INSTANT_YIELD)
	kUtility.SetYields(m_piInstantYield, "Building_InstantYield", "BuildingType", szBuildingType);
	{
		//Building has InstantYield ?
		std::string strKey("Building_InstantYield_MaxRow");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select count(*) from Building_InstantYield where BuildingType = ?");
		}
		pResults->Bind(1, szBuildingType);
		pResults->Step();
		m_iInstantYieldCount = pResults->GetInt(0);
	}
#endif

	kUtility.SetYields(m_piYieldFromProcessModifier, "Building_YieldFromProcessModifier", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldFromProcessModifierGlobal, "Building_YieldFromProcessModifierGlobal", "BuildingType", szBuildingType);

#if defined(MOD_ROG_CORE)
	kUtility.SetYields(m_piGreatWorkYieldChange, "Building_GreatWorkYieldChanges", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldPerEspionageSpy, "Building_YieldPerEspionageSpy", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldChangeWorldWonder, "Building_YieldChangeWorldWonder", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldChangeWorldWonderGlobal, "Building_YieldChangeWorldWonderGlobal", "BuildingType", szBuildingType);
	kUtility.PopulateArrayByValue(m_piResourceQuantityFromPOP, "Resources", "Building_ResourceQuantityFromPOP", "ResourceType", "BuildingType", szBuildingType, "Modifier");
	kUtility.SetYields(m_piYieldPerFriend, "Building_YieldPerFriend", "BuildingType", szBuildingType);
	kUtility.SetYields(m_piYieldPerAlly, "Building_YieldPerAlly", "BuildingType", szBuildingType);

#endif


	//YieldFromYieldYieldChangesGlobal
	{
		m_paYieldFromYieldGlobal = FNEW(CvDoubleYieldInfo[NUM_YIELD_TYPES], c_eCiv5GameplayDLL, 0);
		int idx = 0;

		std::string strResourceTypesKey = "Building_YieldFromYieldPercentGlobal";
		Database::Results* pResourceTypes = kUtility.GetResults(strResourceTypesKey);
		if (pResourceTypes == NULL)
		{
			pResourceTypes = kUtility.PrepareResults(strResourceTypesKey, "select YieldIn, YieldOut, Value from Building_YieldFromYieldPercentGlobal where BuildingType = ?");
		}

		const size_t lenBuildingType = strlen(szBuildingType);
		pResourceTypes->Bind(1, szBuildingType, lenBuildingType, false);

		while (pResourceTypes->Step())
		{
			CvDoubleYieldInfo& pDoubleYieldInfo = m_paYieldFromYieldGlobal[idx];

			const char* szYield = pResourceTypes->GetText("YieldIn");
			pDoubleYieldInfo.m_iYieldIn = (YieldTypes)GC.getInfoTypeForString(szYield, true);

			szYield = pResourceTypes->GetText("YieldOut");
			pDoubleYieldInfo.m_iYieldOut = (YieldTypes)GC.getInfoTypeForString(szYield, true);

			pDoubleYieldInfo.m_iValue = pResourceTypes->GetInt("Value");

			idx++;
		}

		pResourceTypes->Reset();
	}

	//ResourceYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiResourceYieldChange, "Resources", "Yields");

		std::string strKey("Building_ResourceYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Resources.ID as ResourceID, Yields.ID as YieldID, Yield from Building_ResourceYieldChanges inner join Resources on Resources.Type = ResourceType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while(pResults->Step())
		{
			const int ResourceID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiResourceYieldChange[ResourceID][YieldID] = yield;
		}
	}

	//FeatureYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiFeatureYieldChange, "Features", "Yields");

		std::string strKey("Building_FeatureYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Features.ID as FeatureID, Yields.ID as YieldID, Yield from Building_FeatureYieldChanges inner join Features on Features.Type = FeatureType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while(pResults->Step())
		{
			const int FeatureID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiFeatureYieldChange[FeatureID][YieldID] = yield;
		}
	}


	

	//TerrainYieldModier
	{
		kUtility.Initialize2DArray(m_ppaiTerrainYieldModifier, "Terrains", "Yields");

		std::string strKey("Building_TerrainYieldModifier");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Terrains.ID as TerrainID, Yields.ID as YieldID, Yield from Building_TerrainYieldModifier inner join Terrains on Terrains.Type = TerrainType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int TerrainID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiTerrainYieldModifier[TerrainID][YieldID] = yield;
		}
	}

#if defined(MOD_ROG_CORE)
	//Building_DomainFreeExperiencesGlobal
	{
		std::string strKey("Building_DomainFreeExperiencesGlobal");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Domains.ID as DomainID, Experience from Building_DomainFreeExperiencesGlobal inner join Domains on Domains.Type = DomainType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int iDomain = pResults->GetInt(0);
			const int iExperience = pResults->GetInt(1);

			m_piDomainFreeExperienceGlobal[iDomain] += iExperience;
		}

		pResults->Reset();

		//Trim extra memory off container since this is mostly read-only.
		std::map<int, int>(m_piDomainFreeExperienceGlobal).swap(m_piDomainFreeExperienceGlobal);
	}


	//Building_UnitTypePrmoteHealGlobal
	{
		std::string strKey("Building_UnitTypePrmoteHealGlobal");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Units.ID as UnitID, Heal from Building_UnitTypePrmoteHealGlobal inner join Units on Units.Type = UnitType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int iUnit = pResults->GetInt(0);
			const int iHeal = pResults->GetInt(1);

			m_piUnitTypePrmoteHealGlobal[iUnit] += iHeal;
		}

		pResults->Reset();

		//Trim extra memory off container since this is mostly read-only.
		std::map<int, int>(m_piUnitTypePrmoteHealGlobal).swap(m_piUnitTypePrmoteHealGlobal);
	}
#endif

#if defined(MOD_ROG_CORE)
	//SpecialistYieldChangesLocal
	{
		kUtility.Initialize2DArray(m_ppaiSpecialistYieldChangeLocal, "Specialists", "Yields");

		std::string strKey("Building_SpecialistYieldChangesLocal");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Specialists.ID as SpecialistID, Yields.ID as YieldID, Yield from Building_SpecialistYieldChangesLocal inner join Specialists on Specialists.Type = SpecialistType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int SpecialistID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiSpecialistYieldChangeLocal[SpecialistID][YieldID] = yield;
		}
	}

	//ImprovementYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiImprovementYieldChange, "Improvements", "Yields");

		std::string strKey("Building_ImprovementYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Improvements.ID as ImprovementID, Yields.ID as YieldID, Yield from Building_ImprovementYieldChanges inner join Improvements on Improvements.Type = ImprovementType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int ImprovementID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiImprovementYieldChange[ImprovementID][YieldID] = yield;
		}
	}
	//ImprovementYieldChangesGlobal
	{
		kUtility.Initialize2DArray(m_ppaiImprovementYieldChangeGlobal, "Improvements", "Yields");

		std::string strKey("Building_ImprovementYieldChangesGlobal");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Improvements.ID as ImprovementID, Yields.ID as YieldID, Yield from Building_ImprovementYieldChangesGlobal inner join Improvements on Improvements.Type = ImprovementType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int ImprovementID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiImprovementYieldChangeGlobal[ImprovementID][YieldID] = yield;
		}
	}

	{
		kUtility.Initialize2DArray(m_ppiFeatureYieldChangesGlobal, "Features", "Yields");

		std::string strKey("Building_FeatureYieldChangesGlobal");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Features.ID as FeatureID, Yields.ID as YieldID, Yield from Building_FeatureYieldChangesGlobal inner join Features on Features.Type = FeatureType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int FeatureID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiFeatureYieldChangesGlobal[FeatureID][YieldID] = yield;
		}
	}

	{
		kUtility.Initialize2DArray(m_ppiTerrainYieldChangesGlobal, "Terrains", "Yields");

		std::string strKey("Building_TerrainYieldChangesGlobal");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Terrains.ID as TerrainID, Yields.ID as YieldID, Yield from Building_TerrainYieldChangesGlobal inner join Terrains on Terrains.Type = TerrainType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int TerrainID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppiTerrainYieldChangesGlobal[TerrainID][YieldID] = yield;
		}
	}

	//xTerrainYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiYieldPerXTerrain, "Terrains", "Yields");

		std::string strKey("Building_YieldPerXTerrainTimes100");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Terrains.ID as TerrainID, Yields.ID as YieldID, Yield from Building_YieldPerXTerrainTimes100 inner join Terrains on Terrains.Type = TerrainType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int TerrainID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiYieldPerXTerrain[TerrainID][YieldID] = yield;
		}
	}
	//xFeatureYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiYieldPerXFeature, "Features", "Yields");

		std::string strKey("Building_YieldPerXFeatureTimes100");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Features.ID as FeatureID, Yields.ID as YieldID, Yield from Building_YieldPerXFeatureTimes100 inner join Features on Features.Type = FeatureType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int FeatureID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiYieldPerXFeature[FeatureID][YieldID] = yield;
		}
	}


	//Building_YieldChangesPerPopInEmpire
	{
		std::string strKey("Building_YieldChangesPerPopInEmpire");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Yields.ID as YieldID, Yield from Building_YieldChangesPerPopInEmpire inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int iYieldType = pResults->GetInt(0);
			const int iYield = pResults->GetInt(1);

			m_piYieldChangePerPopInEmpire[iYieldType] += iYield;
		}

		pResults->Reset();

		//Trim extra memory off container since this is mostly read-only.
		std::map<int, int>(m_piYieldChangePerPopInEmpire).swap(m_piYieldChangePerPopInEmpire);
	}

	//Building_ResourceYieldChangesGlobal
	{
		std::string strKey("Building_ResourceYieldChangesGlobal");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Resources.ID as ResourceID, Yields.ID as YieldID, Yield from Building_ResourceYieldChangesGlobal inner join Resources on Resources.Type = ResourceType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int iResource = pResults->GetInt(0);
			const int iYieldType = pResults->GetInt(1);
			const int iYield = pResults->GetInt(2);

			m_ppiResourceYieldChangeGlobal[iResource][iYieldType] += iYield;
		}

		pResults->Reset();

		//Trim extra memory off container since this is mostly read-only.
		std::map<int, std::map<int, int>>(m_ppiResourceYieldChangeGlobal).swap(m_ppiResourceYieldChangeGlobal);
	}



#endif
	
	{
		//Building Free Units
		std::string strKey("Building_FreeUnits_MaxRow");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select count(*) from Building_FreeUnits where BuildingType = ?");
		}
		pResults->Bind(1, szBuildingType);
		pResults->Step();
		m_iNumFreeUnit = pResults->GetInt(0);
		pResults->Reset();

		//Building Free Spec Units
		std::string strKey2("Building_FreeSpecUnits_MaxRow");
		pResults = kUtility.GetResults(strKey2);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey2, "select count(*) from Building_FreeSpecUnits where BuildingType = ?");
		}
		pResults->Bind(1, szBuildingType);
		pResults->Step();
		m_iNumFreeUnitTotal = m_iNumFreeUnit;
		m_iNumFreeUnitTotal += pResults->GetInt(0);
		pResults->Reset();

		m_pFreeUnits = new std::pair<UnitTypes, int>[m_iNumFreeUnitTotal];
	}
	{
		std::string strKey("Building_FreeUnits");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Units.ID as UnitID, NumUnits from Building_FreeUnits inner join Units on Units.Type = UnitType where BuildingType = ?");
		}
		pResults->Bind(1, szBuildingType);
		int idx = 0;
		while (pResults->Step())
		{
			const int UnitID = pResults->GetInt(0);
			const int iUnitNum = pResults->GetInt(1);
			m_pFreeUnits[idx] = std::make_pair((UnitTypes)UnitID, iUnitNum);
			idx++;
		}
		pResults->Reset();

		std::string strKey2("Building_FreeSpecUnits");
		pResults = kUtility.GetResults(strKey2);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey2, "select Units.ID as UnitID, NumUnits from Building_FreeSpecUnits inner join Units on Units.Type = UnitType where BuildingType = ?");
		}
		pResults->Bind(1, szBuildingType);
		while (pResults->Step())
		{
			const int UnitID = pResults->GetInt(0);
			const int iUnitNum = pResults->GetInt(1);
			m_pFreeUnits[idx] = std::make_pair((UnitTypes)UnitID, iUnitNum);
			idx++;
		}
		pResults->Reset();
	}

#ifdef MOD_API_BUILDING_ENABLE_PURCHASE_UNITS
	//Buildings enable city to purchase units.
	{
		if (MOD_API_BUILDING_ENABLE_PURCHASE_UNITS) {
			for (int i = 0; i < NUM_YIELD_TYPES; i++) {
				char namedText[512];
				sprintf_s(namedText, "select count(*) from Building_EnableUnitPurchase inner join Yields on Yields.Type = YieldType where Yields.ID = %d and BuildingType = ?", i);
				char cstrKey[512];
				sprintf_s(cstrKey, "Building_EnableUnitPurchase_%d_Count", i);
				std::string strKey(cstrKey);
				auto pResultAllowUnitCount = kUtility.GetResults(strKey);
				if (pResultAllowUnitCount == NULL)
				{
					pResultAllowUnitCount = kUtility.PrepareResults(strKey, namedText);
				}

				pResultAllowUnitCount->Bind(1, szBuildingType);

				pResultAllowUnitCount->Step();
				m_iNumAllowPurchaseUnits[i] = pResultAllowUnitCount->GetInt(0);

				pResultAllowUnitCount->Reset();
				m_piAllowPurchaseUnits[i] = new std::pair<UnitClassTypes, int>[m_iNumAllowPurchaseUnits[i]];
			}
		}
	}

	{
		if (MOD_API_BUILDING_ENABLE_PURCHASE_UNITS) {
			for (int i = 0; i < NUM_YIELD_TYPES; i++) {
				char cstrKey[512];
				sprintf_s(cstrKey, "Building_EnableUnitPurchase_%d", i);
				std::string strKey(cstrKey);
				char query[512];
				sprintf_s(query, "select UnitClasses.ID as UnitClasseID, Building_EnableUnitPurchase.CostModifier as CostModifier from Building_EnableUnitPurchase\
				inner join Yields on Yields.Type = YieldType inner join UnitClasses on UnitClasses.Type = UnitClassType where Yields.ID = %d and BuildingType = ?", i);
				auto pResultAllowUnit = kUtility.GetResults(strKey);
				if (pResultAllowUnit == NULL)
				{
					pResultAllowUnit = kUtility.PrepareResults(strKey, query);
				}
				pResultAllowUnit->Bind(1, szBuildingType);
				int idx = 0;
				while (pResultAllowUnit->Step()) {
					const int UnitClasseID = pResultAllowUnit->GetInt(0);
					const int CostModifier = pResultAllowUnit->GetInt(1);
					m_piAllowPurchaseUnits[i][idx] = std::make_pair((UnitClassTypes)UnitClasseID, CostModifier);
					idx++;
				}
			}
		}
	}
#endif // MOD_API_BUILDING_ENABLE_PURCHASE_UNITS

	//TerrainYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiTerrainYieldChange, "Terrains", "Yields");

		std::string strKey("Building_TerrainYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Terrains.ID as TerrainID, Yields.ID as YieldID, Yield from Building_TerrainYieldChanges inner join Terrains on Terrains.Type = TerrainType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while(pResults->Step())
		{
			const int TerrainID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiTerrainYieldChange[TerrainID][YieldID] = yield;
		}
	}
	
#if defined(MOD_API_UNIFIED_YIELDS) && defined(MOD_API_PLOT_YIELDS)
	//PlotYieldChanges
	if (MOD_API_UNIFIED_YIELDS && MOD_API_PLOT_YIELDS)
	{
		kUtility.Initialize2DArray(m_ppaiPlotYieldChange, "Plots", "Yields");

		std::string strKey("Building_PlotYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Plots.ID as PlotID, Yields.ID as YieldID, Yield from Building_PlotYieldChanges inner join Plots on Plots.Type = PlotType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while(pResults->Step())
		{
			const int PlotID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiPlotYieldChange[PlotID][YieldID] = yield;
		}
	}
#endif

	//SpecialistYieldChanges
	{
		kUtility.Initialize2DArray(m_ppaiSpecialistYieldChange, "Specialists", "Yields");

		std::string strKey("Building_SpecialistYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Specialists.ID as SpecialistID, Yields.ID as YieldID, Yield from Building_SpecialistYieldChanges inner join Specialists on Specialists.Type = SpecialistType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while(pResults->Step())
		{
			const int SpecialistID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiSpecialistYieldChange[SpecialistID][YieldID] = yield;
		}
	}


	//ImprovementYieldModifiers
	{
		kUtility.Initialize2DArray(m_ppaiImprovementYieldModifier, "Improvements", "Yields");

		std::string strKey("Building_ImprovementYieldModifiers");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Improvements.ID as ImprovementID, Yields.ID as YieldID, Yield from Building_ImprovementYieldModifiers inner join Improvements on Improvements.Type = ImprovementType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int ImprovementID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiImprovementYieldModifier[ImprovementID][YieldID] = yield;
		}
	}


	//SpecialistYieldModifiers
	{
		kUtility.Initialize2DArray(m_ppaiSpecialistYieldModifier, "Specialists", "Yields");

		std::string strKey("Building_SpecialistYieldModifiers");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Specialists.ID as SpecialistID, Yields.ID as YieldID, Yield from Building_SpecialistYieldModifiers inner join Specialists on Specialists.Type = SpecialistType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int SpecialistID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiSpecialistYieldModifier[SpecialistID][YieldID] = yield;
		}
	}


	//Building_SpecialistYieldModifiersGlobal
	{

		kUtility.Initialize2DArray(m_ppaiSpecialistYieldModifierGlobal, "Specialists", "Yields");

		std::string strKey("Building_SpecialistYieldModifiersGlobal");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Specialists.ID as SpecialistID, Yields.ID as YieldID, Yield from Building_SpecialistYieldModifiersGlobal inner join Specialists on Specialists.Type = SpecialistType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int SpecialistID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiSpecialistYieldModifierGlobal[SpecialistID][YieldID] = yield;
		}
	}


	//FeatureYieldModifiers
	{
		kUtility.Initialize2DArray(m_ppaiFeatureYieldModifier, "Features", "Yields");

		std::string strKey("Building_FeatureYieldModifiers");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Features.ID as FeatureID, Yields.ID as YieldID, Yield from Building_FeatureYieldModifiers inner join Features on Features.Type = FeatureType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int FeatureID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiFeatureYieldModifier[FeatureID][YieldID] = yield;
		}
	}

	//ResourceYieldModifiers
	{
		kUtility.Initialize2DArray(m_ppaiResourceYieldModifier, "Resources", "Yields");

		std::string strKey("Building_ResourceYieldModifiers");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Resources.ID as ResourceID, Yields.ID as YieldID, Yield from Building_ResourceYieldModifiers inner join Resources on Resources.Type = ResourceType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while(pResults->Step())
		{
			const int ResourceID = pResults->GetInt(0);
			const int YieldID = pResults->GetInt(1);
			const int yield = pResults->GetInt(2);

			m_ppaiResourceYieldModifier[ResourceID][YieldID] = yield;
		}
	}

	//BuildingClassYieldChanges
	{
		kUtility.Initialize2DArray(m_ppiBuildingClassYieldChanges, "BuildingClasses", "Yields");

		std::string strKey("Building_BuildingClassYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if(pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select BuildingClasses.ID as BuildingClassID, Yields.ID as YieldID, YieldChange from Building_BuildingClassYieldChanges inner join BuildingClasses on BuildingClasses.Type = BuildingClassType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while(pResults->Step())
		{
			const int BuildingClassID = pResults->GetInt(0);
			const int iYieldID = pResults->GetInt(1);
			const int iYieldChange = pResults->GetInt(2);

			m_ppiBuildingClassYieldChanges[BuildingClassID][iYieldID] = iYieldChange;
		}
	}


#if defined(MOD_ROG_CORE)
	//BuildingClassYieldModifiers
	{
		kUtility.Initialize2DArray(m_ppiBuildingClassYieldModifiers, "BuildingClasses", "Yields");

		std::string strKey("Building_BuildingClassYieldModifiers");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select BuildingClasses.ID as BuildingClassID, Yields.ID as YieldID, Modifier from Building_BuildingClassYieldModifiers inner join BuildingClasses on BuildingClasses.Type = BuildingClassType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int BuildingClassID = pResults->GetInt(0);
			const int iYieldID = pResults->GetInt(1);
			const int iYieldModifier = pResults->GetInt(2);

			m_ppiBuildingClassYieldModifiers[BuildingClassID][iYieldID] = iYieldModifier;
		}
	}


	//BuildingClassLocalYieldChanges
	{
		kUtility.Initialize2DArray(m_ppiBuildingClassLocalYieldChanges, "BuildingClasses", "Yields");

		std::string strKey("Building_BuildingClassLocalYieldChanges");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select BuildingClasses.ID as BuildingClassID, Yields.ID as YieldID, YieldChange from Building_BuildingClassLocalYieldChanges inner join BuildingClasses on BuildingClasses.Type = BuildingClassType inner join Yields on Yields.Type = YieldType where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int BuildingClassID = pResults->GetInt(0);
			const int iYieldID = pResults->GetInt(1);
			const int iYieldChange = pResults->GetInt(2);

			m_ppiBuildingClassLocalYieldChanges[BuildingClassID][iYieldID] = iYieldChange;
		}
	}
#endif

#if defined(MOD_BUILDING_IMPROVEMENT_RESOURCES)
	//Building_ResourceFromImprovement
	{
		std::string strKey("Building_ResourceFromImprovement");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select Resources.ID as ResourcesID, Improvements.ID as ImprovementsID, Value from Building_ResourceFromImprovement inner join Resources on Resources.Type = ResourceType inner join Improvements on ImprovementType = Improvements.Type where BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int iResource = pResults->GetInt(0);
			const int iImprovement = pResults->GetInt(1);
			const int iValue = pResults->GetInt(2);

			m_piiResourceFromImprovement.insert(std::make_pair(iResource, std::make_pair(iImprovement, iValue)));
		}

		pResults->Reset();

		//Trim extra memory off container since this is mostly read-only.
		std::multimap<int, std::pair<int, int>>(m_piiResourceFromImprovement).swap(m_piiResourceFromImprovement);
	}
#endif

	{
		//Initialize Theming Bonuses
		const int iNumThemes = MAX_THEMING_BONUSES; /* 12 */
		m_paThemingBonusInfo = FNEW(CvThemingBonusInfo[iNumThemes], c_eCiv5GameplayDLL, 0);
		int idx = 0;

		std::string strResourceTypesKey = "Building_ThemingBonuses";
		Database::Results* pResourceTypes = kUtility.GetResults(strResourceTypesKey);
		if(pResourceTypes == NULL)
		{
#if defined(MOD_API_EXTENSIONS)
			pResourceTypes = kUtility.PrepareResults(strResourceTypesKey, "select Bonus, Description, SameEra, UniqueEras, ConsecutiveEras, MustBeArt, MustBeArtifact, MustBeEqualArtArtifact, RequiresOwner, RequiresAnyButOwner, RequiresSamePlayer, RequiresUniquePlayers, AIPriority from Building_ThemingBonuses where BuildingType = ?");
#else
			pResourceTypes = kUtility.PrepareResults(strResourceTypesKey, "select Bonus, Description, SameEra, UniqueEras, MustBeArt, MustBeArtifact, MustBeEqualArtArtifact, RequiresOwner, RequiresAnyButOwner, RequiresSamePlayer, RequiresUniquePlayers, AIPriority from Building_ThemingBonuses where BuildingType = ?");
#endif
		}

		const size_t lenBuildingType = strlen(szBuildingType);
		pResourceTypes->Bind(1, szBuildingType, lenBuildingType, false);

		while(pResourceTypes->Step())
		{
			CvThemingBonusInfo& pThemingInfo = m_paThemingBonusInfo[idx];

			pThemingInfo.m_iBonus = pResourceTypes->GetInt("Bonus");
			pThemingInfo.m_strDescription = pResourceTypes->GetText("Description");
			pThemingInfo.m_bSameEra = pResourceTypes->GetBool("SameEra");
			pThemingInfo.m_bUniqueEras = pResourceTypes->GetBool("UniqueEras");
#if defined(MOD_API_EXTENSIONS)
			pThemingInfo.m_bConsecutiveEras = pResourceTypes->GetBool("ConsecutiveEras");
#endif
			pThemingInfo.m_bMustBeArt = pResourceTypes->GetBool("MustBeArt");
			pThemingInfo.m_bMustBeArtifact = pResourceTypes->GetBool("MustBeArtifact");
			pThemingInfo.m_bMustBeEqualArtArtifact = pResourceTypes->GetBool("MustBeEqualArtArtifact");
			pThemingInfo.m_bRequiresOwner = pResourceTypes->GetBool("RequiresOwner");
			pThemingInfo.m_bRequiresAnyButOwner = pResourceTypes->GetBool("RequiresAnyButOwner");
			pThemingInfo.m_bRequiresSamePlayer = pResourceTypes->GetBool("RequiresSamePlayer");
			pThemingInfo.m_bRequiresUniquePlayers = pResourceTypes->GetBool("RequiresUniquePlayers");
			pThemingInfo.m_iAIPriority = pResourceTypes->GetInt("AIPriority");

			idx++;
		}

		m_iNumThemingBonuses = idx;
		pResourceTypes->Reset();
	}


#ifdef MOD_BUILDINGS_YIELD_FROM_OTHER_YIELD
	if (MOD_BUILDINGS_YIELD_FROM_OTHER_YIELD)
	{
		for (size_t i = 0; i < NUM_YIELD_TYPES; i++)
		{
			for (size_t j = 0; j < NUM_YIELD_TYPES; j++)
			{
				m_ppiYieldFromOtherYield[i][j][0] = 0;
				m_ppiYieldFromOtherYield[i][j][1] = 0;
			}
		}
		m_bHasYieldFromOtherYield = false;

		std::string strKey("Building_YieldFromOtherYield");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == NULL)
		{
			pResults = kUtility.PrepareResults(strKey, "select y1.ID, y2.ID, b.InYieldValue, b.OutYieldValue \
					from Building_YieldFromOtherYield b \
				    inner join Yields y1 on b.OutYieldType = y1.Type \
					inner join Yields y2 on b.InYieldType = y2.Type \
					where b.BuildingType = ?");
		}

		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const int OutYieldTypeID = pResults->GetInt(0);
			const int InYieldTypeID = pResults->GetInt(1);
			const int InYieldValue = pResults->GetInt(2);
			const int OutYieldValue = pResults->GetInt(3);

			if (InYieldValue != 0 && OutYieldValue != 0)
			{
				m_ppiYieldFromOtherYield[OutYieldTypeID][InYieldTypeID][YieldFromYield::IN_VALUE] = InYieldValue;
				m_ppiYieldFromOtherYield[OutYieldTypeID][InYieldTypeID][YieldFromYield::OUT_VALUE] = OutYieldValue;
				m_bHasYieldFromOtherYield = true;
			}
		}
		pResults->Reset();
	}
#endif

	// int GetTradeRouteFromTheCityYields(YieldTypes eYieldTypes);
	{
		for (size_t i = 0; i < NUM_YIELD_TYPES; i++)
		{
			m_aTradeRouteFromTheCityYields[i] = 0;
		}

		std::string strKey("Building_TradeRouteFromTheCityYields");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == nullptr)
		{
			pResults = kUtility.PrepareResults(strKey, "select YieldType, YieldValue from Building_TradeRouteFromTheCityYields where BuildingType = ?");
		}
		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const auto yieldType = (YieldTypes) GC.getInfoTypeForString(pResults->GetText(0));
			const int yieldValue = pResults->GetInt(1);
			if (yieldType >= 0 && yieldType < NUM_YIELD_TYPES)
			{
				m_aTradeRouteFromTheCityYields[yieldType] = yieldValue;
			}
		}

		pResults->Reset();
	}

	// int GetTradeRouteFromTheCityYieldsPerEra(YieldTypes eYieldTypes);
	{
		for (size_t i = 0; i < NUM_YIELD_TYPES; i++)
		{
			m_aTradeRouteFromTheCityYieldsPerEra[i] = 0;
		}

		std::string strKey("Building_TradeRouteFromTheCityYieldsPerEra");
		Database::Results* pResults = kUtility.GetResults(strKey);
		if (pResults == nullptr)
		{
			pResults = kUtility.PrepareResults(strKey, "select YieldType, YieldValue from Building_TradeRouteFromTheCityYieldsPerEra where BuildingType = ?");
		}
		pResults->Bind(1, szBuildingType);

		while (pResults->Step())
		{
			const auto yieldType = (YieldTypes) GC.getInfoTypeForString(pResults->GetText(0));
			const int yieldValue = pResults->GetInt(1);
			if (yieldType >= 0 && yieldType < NUM_YIELD_TYPES)
			{
				m_aTradeRouteFromTheCityYieldsPerEra[yieldType] = yieldValue;
			}
		}

		pResults->Reset();
	}

#ifdef MOD_GLOBAL_CITY_SCALES
	m_bEnableAllCityScaleGrowth = kResults.GetBool("EnableAllCityScaleGrowth");
	auto* strCityScale = kResults.GetText("EnableCityScaleGrowth");
	if (strCityScale != nullptr)
	{
		int len = strlen(strCityScale);
		if (len > 0)
		{
			std::string strKey("Building_EnableCityScaleGrowth");
			Database::Results* pResults = kUtility.GetResults(strKey);
			if (pResults == NULL)
			{
				pResults = kUtility.PrepareResults(strKey, "select ID from CityScales where Type = ?");
			}

			pResults->Bind(1, strCityScale);
			if (pResults->Step())
			{
				m_eEnableCityScaleGrowth = (CityScaleTypes)pResults->GetInt(0);
			}
		}
	}
#endif

	return true;
}

/// Class of this building
int CvBuildingEntry::GetBuildingClassType() const
{
	return m_iBuildingClassType;
}

const CvBuildingClassInfo& CvBuildingEntry::GetBuildingClassInfo() const
{
	if(m_pkBuildingClassInfo == NULL)
	{
		const char* szError = "ERROR: Building does not contain valid BuildingClass type!!";
		GC.LogMessage(szError);
		CvAssertMsg(false, szError);
	}

#pragma warning ( push )
#pragma warning ( disable : 6011 ) // Dereferencing NULL pointer
	return *m_pkBuildingClassInfo;
#pragma warning ( pop )
}

/// Does this building require a city built on or next to a specific terrain type?
int CvBuildingEntry::GetNearbyTerrainRequired() const
{
	return m_iNearbyTerrainRequired;
}

/// Does this building need the absence of a terrain under the city?
int CvBuildingEntry::GetProhibitedCityTerrain() const
{
	return m_iProhibitedCityTerrain;
}

/// Does a Victory need to be active for this building to be buildable?
int CvBuildingEntry::GetVictoryPrereq() const
{
	return m_iVictoryPrereq;
}

/// Do you get this building for free if start in a later era?
int CvBuildingEntry::GetFreeStartEra() const
{
	return m_iFreeStartEra;
}

/// Is this building unbuildable if start in a later era?
int CvBuildingEntry::GetMaxStartEra() const
{
	return m_iMaxStartEra;
}

/// Tech that makes this building obsolete
int CvBuildingEntry::GetObsoleteTech() const
{
	return m_iObsoleteTech;
}

/// Tech that improves the yield from this building
int CvBuildingEntry::GetEnhancedYieldTech() const
{
	return m_iEnhancedYieldTech;
}

/// ... or provides tourism from this building
int CvBuildingEntry::GetTechEnhancedTourism() const
{
	return m_iTechEnhancedTourism;
}

/// How much GPT does this Building cost?
int CvBuildingEntry::GetGoldMaintenance() const
{
	return m_iGoldMaintenance;
}

/// Upgraded version of this building
int CvBuildingEntry::GetReplacementBuildingClass() const
{
	return m_iReplacementBuildingClass;
}

/// Techs required for this building
int CvBuildingEntry::GetPrereqAndTech() const
{
	return m_iPrereqAndTech;
}

int CvBuildingEntry::GetTechNoPrereqClasses() const
{
	return m_iTechNoPrereqClasses;
}

/// Policy branch required for this building
int CvBuildingEntry::GetPolicyBranchType() const
{
	return m_iPolicyBranchType;
}

// Policy  required for this building
int CvBuildingEntry::GetPolicyNeededType() const
{
	return m_iPolicyNeededType;
}

/// Is this building purchaseable in any city?
bool CvBuildingEntry::IsPuppetPurchaseOverride() const
{
	return m_bPuppetPurchaseOverride;
}
/// Does this building unlock purchasing in any city?
bool CvBuildingEntry::IsAllowsPuppetPurchase() const
{
	return m_bAllowsPuppetPurchase;
}

/// What SpecialistType is allowed by this Building
int CvBuildingEntry::GetSpecialistType() const
{
	return m_iSpecialistType;
}

/// How many SpecialistTypes are allowed by this Building
int CvBuildingEntry::GetSpecialistCount() const
{
	return m_iSpecialistCount;
}

/// Extra culture from every specialist
int CvBuildingEntry::GetSpecialistExtraCulture() const
{
	return m_iSpecialistExtraCulture;
}

/// How many GPP does this Building provide (linked to the SpecialistType)
int CvBuildingEntry::GetGreatPeopleRateChange() const
{
	return m_iGreatPeopleRateChange;
}

/// What GreatWorkType is allowed by this Building
GreatWorkSlotType CvBuildingEntry::GetGreatWorkSlotType() const
{
	return m_eGreatWorkSlotType;
}

#if defined(MOD_GLOBAL_GREATWORK_YIELDTYPES)
/// What YieldType is generated by Great Works in this Building
YieldTypes CvBuildingEntry::GetGreatWorkYieldType() const
{
	return m_eGreatWorkYieldType;
}
#endif

/// How many great works are allowed by this Building
int CvBuildingEntry::GetGreatWorkCount() const
{
	return m_iGreatWorkCount;
}

/// Does this building come with a built-in Great Work?
GreatWorkType CvBuildingEntry::GetFreeGreatWork() const
{
	return m_eFreeGreatWork;
}

/// Free building in each city from this building/wonder
int CvBuildingEntry::GetFreeBuildingClass() const
{
	return m_iFreeBuildingClass;
}

/// Free building in the city that builds this building/wonder
int CvBuildingEntry::GetFreeBuildingThisCity() const
{
	return m_iFreeBuildingThisCity;
}

/// Does this building give all units a promotion for free instantly?
int CvBuildingEntry::GetFreePromotion() const
{
	return m_iFreePromotion;
}

/// Does this building give all units a promotion for free instantly?
int CvBuildingEntry::GetFreePromotion2() const
{
	return m_iFreePromotion2;
}

/// Does this building give all units a promotion for free instantly?
int CvBuildingEntry::GetFreePromotion3() const
{
	return m_iFreePromotion3;
}

/// Does this building give units a promotion when trained from this city?
int CvBuildingEntry::GetTrainedFreePromotion() const
{
	return m_iTrainedFreePromotion;
}

/// Does this building get rid of an undesirable promotion?
int CvBuildingEntry::GetFreePromotionRemoved() const
{
	return m_iFreePromotionRemoved;
}

/// Shields to construct the building
int CvBuildingEntry::GetProductionCost() const
{
	return m_iProductionCost;
}

/// Faith to construct the unit (as a percentage of cost of next Great Prophet)
int CvBuildingEntry::GetFaithCost() const
{
	return m_iFaithCost;
}

/// Production value per League member to construct the building
int CvBuildingEntry::GetLeagueCost() const
{
	return m_iLeagueCost;
}

/// Additional cost based on the number of cities in the empire
int CvBuildingEntry::GetNumCityCostMod() const
{
	return m_iNumCityCostMod;
}

/// Does this Building modify any hurry costs
int CvBuildingEntry::GetHurryCostModifier() const
{
	return m_iHurryCostModifier;
}

/// Number of cities required to build this?
int CvBuildingEntry::GetNumCitiesPrereq() const
{
	return m_iNumCitiesPrereq;
}

/// Do we need a unit at a certain level to build this?
int CvBuildingEntry::GetUnitLevelPrereq() const
{
	return m_iUnitLevelPrereq;
}

/// Multiplier to the rate of accumulating culture for policies
int CvBuildingEntry::GetCultureRateModifier() const
{
	return m_iCultureRateModifier;
}

/// Multiplier to the rate of accumulating culture for policies in all Cities
int CvBuildingEntry::GetGlobalCultureRateModifier() const
{
	return m_iGlobalCultureRateModifier;
}

/// Change in spawn rate for great people
int CvBuildingEntry::GetGreatPeopleRateModifier() const
{
	return m_iGreatPeopleRateModifier;
}

/// Change global spawn rate for great people
int CvBuildingEntry::GetGlobalGreatPeopleRateModifier() const
{
	return m_iGlobalGreatPeopleRateModifier;
}

/// Change in spawn rate for great generals
int CvBuildingEntry::GetGreatGeneralRateModifier() const
{
	return m_iGreatGeneralRateModifier;
}

/// Gold received when great person expended
int CvBuildingEntry::GetGreatPersonExpendGold() const
{
	return m_iGreatPersonExpendGold;
}

/// Reduces cost of unit upgrades?
int CvBuildingEntry::GetUnitUpgradeCostMod() const
{
	return m_iUnitUpgradeCostMod;
}

/// Percentage increase in the length of Golden Ages
int CvBuildingEntry::GetGoldenAgeModifier() const
{
	return m_iGoldenAgeModifier;
}

/// Free experience for units built in this city
int CvBuildingEntry::GetFreeExperience() const
{
	return m_iFreeExperience;
}

/// Free experience for all player units
int CvBuildingEntry::GetGlobalFreeExperience() const
{
	return m_iGlobalFreeExperience;
}

/// Percentage of food retained after city growth
int CvBuildingEntry::GetFoodKept() const
{
	return m_iFoodKept;
}

/// Does this building allow airlifts?
bool CvBuildingEntry::IsAirlift() const
{
	return m_bAirlift;
}

/// Modifier to city air defense
int CvBuildingEntry::GetAirModifier() const
{
	return m_iAirModifier;
}

/// Modifier to city nuke defense
int CvBuildingEntry::GetNukeModifier() const
{
	return m_iNukeModifier;
}

/// Will this building cause a big problem (meltdown) if the city is hit with a nuke?
int CvBuildingEntry::GetNukeExplosionRand() const
{
	return m_iNukeExplosionRand;
}

/// Improvement in worker speed
int CvBuildingEntry::GetWorkerSpeedModifier() const
{
	return m_iWorkerSpeedModifier;
}

/// Improvement in military unit production
int CvBuildingEntry::GetMilitaryProductionModifier() const
{
	return m_iMilitaryProductionModifier;
}

/// Improvement in space race component production
int CvBuildingEntry::GetSpaceProductionModifier() const
{
	return m_iSpaceProductionModifier;
}

/// Improvement in space race component production in all cities
int CvBuildingEntry::GetGlobalSpaceProductionModifier() const
{
	return m_iGlobalSpaceProductionModifier;
}

/// Improvement in building production
int CvBuildingEntry::GetBuildingProductionModifier() const
{
	return m_iBuildingProductionModifier;
}

/// Improvement in wonder production
int CvBuildingEntry::GetWonderProductionModifier() const
{
	return m_iWonderProductionModifier;
}

/// Trade route gold modifier
int CvBuildingEntry::GetCityConnectionTradeRouteModifier() const
{
	return m_iCityConnectionTradeRouteModifier;
}

/// Increased plunder if city captured
int CvBuildingEntry::GetCapturePlunderModifier() const
{
	return m_iCapturePlunderModifier;
}

/// Change in culture cost to earn a new policy
int CvBuildingEntry::GetPolicyCostModifier() const
{
	return m_iPolicyCostModifier;
}

/// Change in culture cost to earn a new tile
int CvBuildingEntry::GetPlotCultureCostModifier() const
{
	return m_iPlotCultureCostModifier;
}

/// Change in culture cost to earn a new tile
int CvBuildingEntry::GetGlobalPlotCultureCostModifier() const
{
	return m_iGlobalPlotCultureCostModifier;
}

/// Change in gold cost to earn a new tile
int CvBuildingEntry::GetPlotBuyCostModifier() const
{
	return m_iPlotBuyCostModifier;
}

/// Change in gold cost to earn a new tile across the empire
int CvBuildingEntry::GetGlobalPlotBuyCostModifier() const
{
	return m_iGlobalPlotBuyCostModifier;
}

#if defined(MOD_BUILDINGS_CITY_WORKING)
/// Change in number of rings this city can work
int CvBuildingEntry::GetCityWorkingChange() const
{
	return m_iCityWorkingChange;
}

/// Change in number of rings any city can work
int CvBuildingEntry::GetGlobalCityWorkingChange() const
{
	return m_iGlobalCityWorkingChange;
}
#endif

#if defined(MOD_BUILDINGS_CITY_AUTOMATON_WORKERS)
/// Change in number of automatons for this city
int CvBuildingEntry::GetCityAutomatonWorkersChange() const
{
	return m_iCityAutomatonWorkersChange;
}

/// Change in number of automatons for every city
int CvBuildingEntry::GetGlobalCityAutomatonWorkersChange() const
{
	return m_iGlobalCityAutomatonWorkersChange;
}
#endif

/// Required Plot count of the CvArea this City belongs to (Usually used for Water Buildings to prevent Harbors in tiny lakes and such)
int CvBuildingEntry::GetMinAreaSize() const
{
	return m_iMinAreaSize;
}

/// Chance of building surviving after conquest
int CvBuildingEntry::GetConquestProbability() const
{
	return m_iConquestProbability;
}

/// Improvement in unit heal rate from this building
int CvBuildingEntry::GetHealRateChange() const
{
	return m_iHealRateChange;
}


#if defined(MOD_ROG_CORE)
int CvBuildingEntry::GetGlobalCityStrengthMod() const
{
	return m_iGlobalCityStrengthMod;
}

int CvBuildingEntry::GetGlobalRangedStrikeModifier() const
{
	return m_iGlobalRangedStrikeModifier;
}

int CvBuildingEntry::GetResearchTotalCostModifier() const
{
	return m_iResearchTotalCostModifier;
}
int CvBuildingEntry::GetResearchTotalCostModifierGoldenAge() const
{
	return m_iResearchTotalCostModifierGoldenAge;
}

/// Does this Building allow us to Range Strike?
int CvBuildingEntry::CityRangedStrikeModifier() const
{
	return m_iRangedStrikeModifier;
}

int CvBuildingEntry::GetExtraDamageHealPercent() const
{
	return m_iExtraDamageHealPercent;
}
int CvBuildingEntry::GetExtraDamageHeal() const
{
	return m_iExtraDamageHeal;
}

int CvBuildingEntry::GetBombardRange() const
{
	return m_iBombardRange;
}

int CvBuildingEntry::IsBombardIndirect() const
{
	return m_bBombardIndirect;
}


int CvBuildingEntry::GetPopulationChange() const
{
	return m_iPopulationChange;
}

int CvBuildingEntry::GetMinorCivFriendship() const
{
	return m_iMinorCivFriendship;
}

int CvBuildingEntry::GetLiberatedInfluence() const
{
	return m_iLiberatedInfluence;
}


int CvBuildingEntry::GetExtraUnitPlayerInstances() const
{
	return m_iExtraUnitPlayerInstances;
}

int CvBuildingEntry::GetResetDamageValue() const
{
	return m_iResetDamageValue;
}

int CvBuildingEntry::GetReduceDamageValue() const
{
	return m_iReduceDamageValue;
}



int CvBuildingEntry::GetWaterTileDamage() const
{
	return m_iWaterTileDamage;
}

int CvBuildingEntry::GetWaterTileMovementReduce() const
{
	return m_iWaterTileMovementReduce;
}



int CvBuildingEntry::GetWaterTileTurnDamage() const
{
	return m_iWaterTileTurnDamage;
}

int CvBuildingEntry::GetLandTileDamage() const
{
	return m_iLandTileDamage;
}

int CvBuildingEntry::GetLandTileMovementReduce() const
{
	return m_iLandTileMovementReduce;
}

int CvBuildingEntry::GetLandTileTurnDamage() const
{
	return m_iLandTileTurnDamage;
}






int CvBuildingEntry::GetWaterTileDamageGlobal() const
{
	return m_iWaterTileDamageGlobal;
}
int CvBuildingEntry::GetWaterTileMovementReduceGlobal() const
{
	return m_iWaterTileMovementReduceGlobal;
}
int CvBuildingEntry::GetWaterTileTurnDamageGlobal() const
{
	return m_iWaterTileTurnDamageGlobal;
}

int CvBuildingEntry::GetLandTileDamageGlobal() const
{
	return m_iLandTileDamageGlobal;
}
int CvBuildingEntry::GetLandTileMovementReduceGlobal() const
{
	return m_iLandTileMovementReduceGlobal;
}
int CvBuildingEntry::GetLandTileTurnDamageGlobal() const
{
	return m_iLandTileTurnDamageGlobal;
}
#endif

#ifdef MOD_PROMOTION_CITY_DESTROYER
int CvBuildingEntry::GetSiegeKillCitizensModifier() const
{
	return m_iSiegeKillCitizensModifier;
}
#endif

#if defined(MOD_INTERNATIONAL_IMMIGRATION_FOR_SP)
bool CvBuildingEntry::CanAllScaleImmigrantIn() const
{
	return m_bCanAllScaleImmigrantIn;
}
#endif

#ifdef MOD_GLOBAL_CORRUPTION
int CvBuildingEntry::GetCorruptionScoreChange() const
{
	return m_iCorruptionScoreChange;
}

int CvBuildingEntry::GetCorruptionLevelChange() const
{
	return m_iCorruptionLevelChange;
}

int CvBuildingEntry::GetMinCorruptionLevelNeeded() const
{
	return m_iMinCorruptionLevelNeeded;
}

int CvBuildingEntry::GetMaxCorruptionLevelNeeded() const
{
	return m_iMaxCorruptionLevelNeeded;
}

int CvBuildingEntry::GetCorruptionPolicyCostModifier() const
{
	return m_iCorruptionPolicyCostModifier;
}
#endif

int CvBuildingEntry::GetGlobalProductionNeededUnitModifier() const {
	return m_iGlobalProductionNeededUnitModifier;
}
int CvBuildingEntry::GetGlobalProductionNeededBuildingModifier() const {
	return m_iGlobalProductionNeededBuildingModifier;
}
int CvBuildingEntry::GetGlobalProductionNeededProjectModifier() const {
	return m_iGlobalProductionNeededProjectModifier;
}
int CvBuildingEntry::GetGlobalProductionNeededUnitMax() const {
	return m_iGlobalProductionNeededUnitMax;
}
int CvBuildingEntry::GetGlobalProductionNeededBuildingMax() const {
	return m_iGlobalProductionNeededBuildingMax;
}
int CvBuildingEntry::GetGlobalProductionNeededProjectMax() const {
	return m_iGlobalProductionNeededProjectMax;
}

bool CvBuildingEntry::IsDummyBuilding() const {
	return m_bDummyBuilding;
}

bool CvBuildingEntry::IsNoPuppet() const {
	return m_bNoPuppet;
}

int CvBuildingEntry::GetInstantResearchFromFriendlyGreatScientist() const {
	return m_iInstantResearchFromFriendlyGreatScientist;
}

int CvBuildingEntry::GetGlobalGrowthFoodNeededModifier() const {
	return m_iGlobalGrowthFoodNeededModifier;
}

int CvBuildingEntry::GetSecondCapitalsExtraScore() const {
	return m_iSecondCapitalsExtraScore;
}

int CvBuildingEntry::GetFoodKeptFromPollution() const {
	return m_iFoodKeptFromPollution;
}

int CvBuildingEntry::GetExtraAttacks() const
{
	return m_iExtraAttacks;
}

/// Happiness provided by this building
int CvBuildingEntry::GetHappiness() const
{
	return m_iHappiness;
}

/// UnmoddedHappiness provided by this building - NOT affected by a city's pop
int CvBuildingEntry::GetUnmoddedHappiness() const
{
	return m_iUnmoddedHappiness;
}

/// Get percentage modifier to overall player happiness
int CvBuildingEntry::GetUnhappinessModifier() const
{
	return m_iUnhappinessModifier;
}

/// HappinessPerCity provided by this building
int CvBuildingEntry::GetHappinessPerCity() const
{
	return m_iHappinessPerCity;
}

/// Happiness per X number of Policies provided by this building
int CvBuildingEntry::GetHappinessPerXPolicies() const
{
	return m_iHappinessPerXPolicies;
}

/// CityCountUnhappinessMod provided by this building
int CvBuildingEntry::GetCityCountUnhappinessMod() const
{
	return m_iCityCountUnhappinessMod;
}

/// NoOccupiedUnhappiness
bool CvBuildingEntry::IsNoOccupiedUnhappiness() const
{
	return m_bNoOccupiedUnhappiness;
}

/// NotNeedOccupied
bool CvBuildingEntry::IsNotNeedOccupied() const
{
	return m_bNotNeedOccupied;
}

/// Population added to every City in the player's empire
int CvBuildingEntry::GetGlobalPopulationChange() const
{
	return m_iGlobalPopulationChange;
}

/// If this # of players have a Tech then the owner of this Building gets that Tech as well
int CvBuildingEntry::GetTechShare() const
{
	return m_iTechShare;
}

/// Number of free techs granted by this building
int CvBuildingEntry::GetFreeTechs() const
{
	return m_iFreeTechs;
}

/// Number of free Policies granted by this building
int CvBuildingEntry::GetFreePolicies() const
{
	return m_iFreePolicies;
}

/// Number of free Great People granted by this building
int CvBuildingEntry::GetFreeGreatPeople() const
{
	return m_iFreeGreatPeople;
}

/// Boost to median tech received from research agreements
int CvBuildingEntry::GetMedianTechPercentChange() const
{
	return m_iMedianTechPercentChange;
}

/// Gold generated by this building
int CvBuildingEntry::GetGold() const
{
	return m_iGold;
}

/// Does a city need to be near a mountain to build this?
bool CvBuildingEntry::IsNearbyMountainRequired() const
{
	return m_bNearbyMountainRequired;
}

/// Does this Building allow us to Range Strike?
bool CvBuildingEntry::IsAllowsRangeStrike() const
{
	return m_bAllowsRangeStrike;
}

/// Modifier to city defense
int CvBuildingEntry::GetDefenseModifier() const
{
	return m_iDefenseModifier;
}

/// Modifier to every City's Building defense
int CvBuildingEntry::GetGlobalDefenseModifier() const
{
	return m_iGlobalDefenseModifier;
}

/// Modifier to city's hit points
int CvBuildingEntry::GetExtraCityHitPoints() const
{
	return m_iExtraCityHitPoints;
}

/// Instant Friendship mod change with City States
int CvBuildingEntry::GetMinorFriendshipChange() const
{
	return m_iMinorFriendshipChange;
}

int CvBuildingEntry::GetMinorFriendshipAnchorChange() const
{
	return m_iMinorFriendshipAnchorChange;
}

int CvBuildingEntry::GetMinorQuestFriendshipMod() const
{
	return m_iMinorQuestFriendshipMod;
}

/// VPs added to overall Team score
int CvBuildingEntry::GetVictoryPoints() const
{
	return m_iVictoryPoints;
}

/// Extra religion spreads from missionaries built in this city
int CvBuildingEntry::GetExtraMissionarySpreads() const
{
	return m_iExtraMissionarySpreads;
}

/// Extra religion pressure emanating from this city
int CvBuildingEntry::GetReligiousPressureModifier() const
{
	return m_iReligiousPressureModifier;
}

/// Modifier to chance of espionage against this city
int CvBuildingEntry::GetEspionageModifier() const
{
	return m_iEspionageModifier;
}

/// Modifier to chance of espionage against all cities
int CvBuildingEntry::GetGlobalEspionageModifier() const
{
	return m_iGlobalEspionageModifier;
}

int CvBuildingEntry::GetGlobalEspionageSpeedModifier() const
{
	return m_iGlobalEspionageSpeedModifier;
}

/// Extra spies after this is built
int CvBuildingEntry::GetExtraSpies() const
{
	return m_iExtraSpies;
}

/// Increase in rank of all starting spies
int CvBuildingEntry::GetSpyRankChange() const
{
	return m_iSpyRankChange;
}

/// How much the trade recipient gets for a trade route being establish with the city
int CvBuildingEntry::GetTradeRouteRecipientBonus() const
{
	return m_iTradeRouteRecipientBonus;
}

/// How much the trade target gets for a trade route being established with the city
int CvBuildingEntry::GetTradeRouteTargetBonus() const
{
	return m_iTradeRouteTargetBonus;
}

int CvBuildingEntry::GetNumTradeRouteBonus() const
{
	return m_iNumTradeRouteBonus;
}

int CvBuildingEntry::GetTradeRouteSeaDistanceModifier() const
{
	return m_iTradeRouteSeaDistanceModifier;
}

int CvBuildingEntry::GetTradeRouteSeaGoldBonus() const
{
	return m_iTradeRouteSeaGoldBonus;
}

int CvBuildingEntry::GetTradeRouteLandDistanceModifier() const
{
	return m_iTradeRouteLandDistanceModifier;
}

int CvBuildingEntry::GetTradeRouteLandGoldBonus() const
{
	return m_iTradeRouteLandGoldBonus;
}

int CvBuildingEntry::GetGreatScientistBeakerModifier() const
{
	return m_iGreatScientistBeakerModifier;
}

/// One-time boost for all existing spies
int CvBuildingEntry::GetInstantSpyRankChange() const
{
	return m_iInstantSpyRankChange;
}

/// Tourism output from Landmarks and Wonders
int CvBuildingEntry::GetLandmarksTourismPercent() const
{
	return m_iLandmarksTourismPercent;
}

/// For the terra cotta army. DOUBLE THE SIZE OF YOUR ARMY
int CvBuildingEntry::GetInstantMilitaryIncrease() const
{
	return m_iInstantMilitaryIncrease;
}

/// Boost to tourism output from Great Works
int CvBuildingEntry::GetGreatWorksTourismModifier() const
{
	return m_iGreatWorksTourismModifier;
}

/// Is an Ideology choice brought on by constructing this building in X cities?
int CvBuildingEntry::GetXBuiltTriggersIdeologyChoice() const
{
	return m_iXBuiltTriggersIdeologyChoice;
}

/// Extra votes to use in leagues
int CvBuildingEntry::GetExtraLeagueVotes() const
{
	return m_iExtraLeagueVotes;
}

#if defined(MOD_RELIGION_CONVERSION_MODIFIERS)
/// Modifier to chance of conversion against this city
int CvBuildingEntry::GetConversionModifier() const
{
	return m_iConversionModifier;
}

/// Modifier to chance of conversion against all cities
int CvBuildingEntry::GetGlobalConversionModifier() const
{
	return m_iGlobalConversionModifier;
}
#endif

/// What ring the engine will try to display this building
int CvBuildingEntry::GetPreferredDisplayPosition() const
{
	return m_iPreferredDisplayPosition;
}

/// index of portrait in the texture sheet
int CvBuildingEntry::GetPortraitIndex() const
{
	return m_iPortraitIndex;
}

#if defined(MOD_NUCLEAR_WINTER_FOR_SP)
bool CvBuildingEntry::IsNoNuclearWinterLocal() const
{
	return m_bNoNuclearWinterLocal;
}
#endif

#if defined(MOD_TROOPS_AND_CROPS_FOR_SP)
int CvBuildingEntry::GetNumCrops() const
{
	return m_iNumCrops;
}
int CvBuildingEntry::GetNumArmee() const
{
	return m_iNumArmee;
}
/// Does this building EnableCrops?
bool CvBuildingEntry::IsEnableCrops() const
{
	return m_bEnableCrops;
}
/// Does this building EnableArmee?
bool CvBuildingEntry::IsEnableArmee() const
{
	return m_bEnableArmee;
}
#endif

/// Is the presence of this building shared with team allies?
bool CvBuildingEntry::IsTeamShare() const
{
	return m_bTeamShare;
}

/// Must this be built in a coastal city?
bool CvBuildingEntry::IsWater() const
{
	return m_bWater;
}

/// Must this be built in a river city?
bool CvBuildingEntry::IsRiver() const
{
	return m_bRiver;
}

/// Must this be built in a city next to FreshWater?
bool CvBuildingEntry::IsFreshWater() const
{
	return m_bFreshWater;
}

#if defined(MOD_MORE_NATURAL_WONDER)
/// Does this building add FreshWater?
bool CvBuildingEntry::IsImmueVolcanoDamage() const
{
	return m_bImmueVolcanoDamage;
}
#endif

#if defined(MOD_API_EXTENSIONS)
/// Does this building add FreshWater?
bool CvBuildingEntry::IsAddsFreshWater() const
{
	return m_bAddsFreshWater;
}

/// Do we need to purchase this building (i.e. can't be built)?
bool CvBuildingEntry::IsPurchaseOnly() const
{
	return m_bPurchaseOnly;
}

bool CvBuildingEntry::IsHumanOnly() const
{
	return m_bHumanOnly;
}
#endif

bool CvBuildingEntry::IsMoveAfterCreated() const
{
	return m_bMoveAfterCreated;
}


#if defined(MOD_ROG_CORE)
/// Change to Great Work yield by type
int CvBuildingEntry::GetGreatWorkYieldChange(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piGreatWorkYieldChange ? m_piGreatWorkYieldChange[i] : -1;
}
/// Array of yield changes to Great Works
int* CvBuildingEntry::GetGreatWorkYieldChangeArray() const
{
	return m_piGreatWorkYieldChange;
}
#endif

/// Must this be built in a city next to Mountain?
bool CvBuildingEntry::IsMountain() const
{
	return m_bMountain;
}

/// Must this be built in a city on a hill?
bool CvBuildingEntry::IsHill() const
{
	return m_bHill;
}

/// Must this be built in a city on Flat ground?
bool CvBuildingEntry::IsFlat() const
{
	return m_bFlat;
}

/// Does this Building Found a Religion?
bool CvBuildingEntry::IsFoundsReligion() const
{
	return m_bFoundsReligion;
}

/// Is this a "Religous" Building? (qualifies it for Production bonuses for Policies, etc.)
bool CvBuildingEntry::IsReligious() const
{
	return m_bIsReligious;
}

/// Is this an obstacle at the edge of your empire (e.g. Great Wall) -- for you AND your teammates
bool CvBuildingEntry::IsBorderObstacle() const
{
	return m_bBorderObstacle;
}

/// Is this an obstacle at the edge of your empire (e.g. Great Wall) -- for just the owning player
bool CvBuildingEntry::IsPlayerBorderObstacle() const
{
	return m_bPlayerBorderObstacle;
}


int CvBuildingEntry::GetNukeInterceptionChance() const
{
	return m_iNukeInterceptionChance;
}

/// Does this trigger drawing a wall around the city
bool CvBuildingEntry::IsCityWall() const
{
	return m_bCityWall;
}

/// Is this building unlocked through religion?
bool CvBuildingEntry::IsUnlockedByBelief() const
{
	return m_bUnlockedByBelief;
}

/// Is this building unlocked through League actions?
bool CvBuildingEntry::IsUnlockedByLeague() const
{
	return m_bUnlockedByLeague;
}

/// Does it have to be built in the Holy City?
bool CvBuildingEntry::IsRequiresHolyCity() const
{
	return m_bRequiresHolyCity;
}

/// Does this building affect spy rates when it is built?
bool CvBuildingEntry::AffectSpiesNow() const
{
	return m_bAffectSpiesNow;
}

// Is this an espionage building that should be disabled when espionage is disabled?
bool CvBuildingEntry::IsEspionage() const
{
	return m_bEspionage;
}

bool CvBuildingEntry::AllowsFoodTradeRoutes() const
{
	return m_bAllowsFoodTradeRoutes;
}

bool CvBuildingEntry::AllowsProductionTradeRoutes() const
{
	return m_bAllowsProductionTradeRoutes;
}

bool CvBuildingEntry::NullifyInfluenceModifier() const
{
	return m_bNullifyInfluenceModifier;
}

/// Does this building define the capital?
bool CvBuildingEntry::IsCapital() const
{
	return m_bCapital;
}

/// Does this building spawn a golden age?
bool CvBuildingEntry::IsGoldenAge() const
{
	return m_bGoldenAge;
}

/// Is the map centered after this building is constructed?
bool CvBuildingEntry::IsMapCentering() const
{
	return m_bMapCentering;
}

/// Can this building never be captured?
bool CvBuildingEntry::IsNeverCapture() const
{
	return m_bNeverCapture;
}

/// Is the building immune to nukes?
bool CvBuildingEntry::IsNukeImmune() const
{
	return m_bNukeImmune;
}


bool CvBuildingEntry::IsExtraAttackOnKill() const
{
	return m_bExtraAttackOnKill;
}


bool CvBuildingEntry::IsForbiddenForeignSpy() const
{
	return m_bIsForbiddenForeignSpy;
}

bool CvBuildingEntry::IsForbiddenForeignSpyGlobal() const
{
	return m_bIsForbiddenForeignSpyGlobal;
}

/// Does the building add an additional of each luxury in city radius
bool CvBuildingEntry::IsExtraLuxuries() const
{
	return m_bExtraLuxuries;
}

/// Begins voting for the diplo victory?
bool CvBuildingEntry::IsDiplomaticVoting() const
{
	return m_bDiplomaticVoting;
}

/// Does the building allow routes over the water
bool CvBuildingEntry::AllowsWaterRoutes() const
{
	return m_bAllowsWaterRoutes;
}

/// Derive property: is this considered a science building?
bool CvBuildingEntry::IsScienceBuilding() const
{
	bool bRtnValue = false;

	if(IsCapital())
	{
		bRtnValue = false;
	}
	else if(GetYieldChange(YIELD_SCIENCE) > 0)
	{
		bRtnValue = true;
	}
	else if(GetYieldChangePerEra(YIELD_SCIENCE) > 0)
	{
		bRtnValue = true;
	}
	else if(GetYieldModifierChangePerEra(YIELD_SCIENCE) > 0)
	{
		bRtnValue = true;
	}
	else if(GetCityStateTradeRouteYieldModifier(YIELD_SCIENCE) > 0)
	{
		bRtnValue = true;
	}
	else if(GetCityStateTradeRouteYieldModifierGlobal(YIELD_SCIENCE) > 0)
	{
		bRtnValue = true;
	}
	else if(GetYieldChangePerPop(YIELD_SCIENCE) > 0)
	{
		bRtnValue = true;
	}
	else if(GetYieldChangePerReligion(YIELD_SCIENCE) > 0)
	{
		bRtnValue = true;
	}
	else if(GetTechEnhancedYieldChange(YIELD_SCIENCE) > 0)
	{
		bRtnValue = true;
	}
	else if(GetYieldModifier(YIELD_SCIENCE) > 0)
	{
		bRtnValue = true;
	}

#if defined(MOD_ROG_CORE)
	else if (GetYieldModifierFromWonder(YIELD_SCIENCE) > 0)
	{
		bRtnValue = true;
	}

#endif
	

	return bRtnValue;
}

/// Retrieve art tag
const char* CvBuildingEntry::GetArtDefineTag() const
{
	return m_strArtDefineTag.c_str();
}

/// Set art tag
void CvBuildingEntry::SetArtDefineTag(const char* szVal)
{
	m_strArtDefineTag = szVal;
}

/// Return whether we should try to find a culture specific variant art tag
const bool CvBuildingEntry::GetArtInfoCulturalVariation() const
{
	return m_bArtInfoCulturalVariation;
}

/// Return whether we should try to find an era specific variant art tag
const bool CvBuildingEntry::GetArtInfoEraVariation() const
{
	return m_bArtInfoEraVariation;
}

/// Return whether we should try to find an era specific variant art tag
const bool CvBuildingEntry::GetArtInfoRandomVariation() const
{
	return m_bArtInfoRandomVariation;
}

const char* CvBuildingEntry::GetWonderSplashAudio() const
{
	return m_strWonderSplashAudio.c_str();
}

CvString CvBuildingEntry::GetThemingBonusHelp() const
{
	return m_strThemingBonusHelp;
}

// ARRAYS

/// Change to yield by type
int CvBuildingEntry::GetYieldChange(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChange ? m_piYieldChange[i] : -1;
}

/// Array of yield changes
int* CvBuildingEntry::GetYieldChangeArray() const
{
	return m_piYieldChange;
}

/// Change to yield by type per era
int CvBuildingEntry::GetYieldChangePerEra(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangePerEra ? m_piYieldChangePerEra[i] : -1;
}

/// Array of yield changes per era
int* CvBuildingEntry::GetYieldChangePerEraArray() const
{
	return m_piYieldChangePerEra;
}
/// Change to yieldModifier by type per era
int CvBuildingEntry::GetYieldModifierChangePerEra(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldModifierChangePerEra ? m_piYieldModifierChangePerEra[i] : -1;
}

/// Array of yieldModifier changes per era
int* CvBuildingEntry::GetYieldModifierChangePerEraArray() const
{
	return m_piYieldModifierChangePerEra;
}
/// Change to yieldModifier by type City State TradeRoute
int CvBuildingEntry::GetCityStateTradeRouteYieldModifier(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piCityStateTradeRouteYieldModifier ? m_piCityStateTradeRouteYieldModifier[i] : -1;
}

/// Change to yieldModifier Global by type City State TradeRoute
int CvBuildingEntry::GetCityStateTradeRouteYieldModifierGlobal(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piCityStateTradeRouteYieldModifierGlobal ? m_piCityStateTradeRouteYieldModifierGlobal[i] : -1;
}

/// Change to yield by type
int CvBuildingEntry::GetYieldChangePerPop(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangePerPop ? m_piYieldChangePerPop[i] : -1;
}

/// Array of yield changes
int* CvBuildingEntry::GetYieldChangePerPopArray() const
{
	return m_piYieldChangePerPop;
}

int CvBuildingEntry::GetYieldFromInternal(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromInternal[i];
}
/// Array of yield changes
int* CvBuildingEntry::GetYieldFromInternalArray() const
{
	return m_piYieldFromInternal;
}

/// Does this Policy grant yields from constructing buildings?
int CvBuildingEntry::GetYieldFromProcessModifier(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromProcessModifier[i];
}
/// Array of yield changes
int* CvBuildingEntry::GetYieldFromProcessModifierArray() const
{
	return m_piYieldFromProcessModifier;
}

int CvBuildingEntry::GetYieldFromProcessModifierGlobal(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromProcessModifierGlobal[i];
}
/// Array of yield changes
int* CvBuildingEntry::GetYieldFromProcessModifierArrayGlobal() const
{
	return m_piYieldFromProcessModifierGlobal;
}


#if defined(MOD_ROG_CORE)

/// Change to yield by type
int CvBuildingEntry::GetYieldChangePerPopInEmpire(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	std::map<int, int>::const_iterator it = m_piYieldChangePerPopInEmpire.find(i);
	if (it != m_piYieldChangePerPopInEmpire.end()) // find returns the iterator to map::end if the key i is not present in the map
	{
		return it->second;
	}

	return 0;
}
#endif

/// Change to yield by type
int CvBuildingEntry::GetYieldChangePerReligion(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangePerReligion ? m_piYieldChangePerReligion[i] : -1;
}

/// Array of yield changes
int* CvBuildingEntry::GetYieldChangePerReligionArray() const
{
	return m_piYieldChangePerReligion;
}

/// Modifier to yield by type
int CvBuildingEntry::GetYieldModifier(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldModifier ? m_piYieldModifier[i] : -1;
}

/// Array of yield modifiers
int* CvBuildingEntry::GetYieldModifierArray() const
{
	return m_piYieldModifier;
}

/// Multiplier to yield by type
int CvBuildingEntry::GetYieldMultiplier(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldMultiplier ? m_piYieldMultiplier[i] : -1;
}

/// Array of yield Multipliers
int* CvBuildingEntry::GetYieldMultiplierArray() const
{
	return m_piYieldMultiplier;
}


#if defined(MOD_ROG_CORE)
/// Does this  grant yields from constructing buildings?
int CvBuildingEntry::GetYieldFromConstruction(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromConstruction[i];
}
/// Array of yield changes
int* CvBuildingEntry::GetYieldFromConstructionArray() const
{
	return m_piYieldFromConstruction;
}

int CvBuildingEntry::GetYieldFromUnitProduction(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromUnitProduction[i];
}
/// Array of yield changes
int* CvBuildingEntry::GetYieldFromUnitProductionArray() const
{
	return m_piYieldFromUnitProduction;
}

int CvBuildingEntry::GetYieldFromBirth(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromBirth[i];
}
/// Array of yield changes
int* CvBuildingEntry::GetYieldFromBirthArray() const
{
	return m_piYieldFromBirth;
}

int CvBuildingEntry::GetYieldFromBorderGrowth(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromBorderGrowth[i];
}
/// Array of yield changes
int* CvBuildingEntry::GetYieldFromBorderGrowthArray() const
{
	return m_piYieldFromBorderGrowth;
}

/// Change to yield if pillaging
int CvBuildingEntry::GetYieldFromPillage(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromPillage ? m_piYieldFromPillage[i] : -1;
}
/// Array of yield changes
int* CvBuildingEntry::GetYieldFromPillageArray() const
{
	return m_piYieldFromPillage;
}

/// Change to yield if pillaging
int CvBuildingEntry::GetYieldFromPillageGlobal(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromPillageGlobal ? m_piYieldFromPillageGlobal[i] : -1;
}
/// Array of yield changes
int* CvBuildingEntry::GetYieldFromPillageGlobalArray() const
{
	return m_piYieldFromPillageGlobal;
}

/// Change to yield if pillaging
int CvBuildingEntry::GetYieldFromPillageGlobalPlayer(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldFromPillageGlobalPlayer ? m_piYieldFromPillageGlobalPlayer[i] : -1;
}
/// Array of yield changes
int* CvBuildingEntry::GetYieldFromPillageGlobalPlayerArray() const
{
	return m_piYieldFromPillageGlobalPlayer;
}

int CvBuildingEntry::GetYieldModifierFromWonder(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldModifierFromWonder ? m_piYieldModifierFromWonder[i] : -1;
}

/// Array of yield modifiers
int* CvBuildingEntry::GetYieldModifierFromWonderArray() const
{
	return m_piYieldModifierFromWonder;
}
#endif



/// Modifier to yield by type in area
int CvBuildingEntry::GetAreaYieldModifier(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piAreaYieldModifier ? m_piAreaYieldModifier[i] : -1;
}

/// Array of yield modifiers in area
int* CvBuildingEntry::GetAreaYieldModifierArray() const
{
	return m_piAreaYieldModifier;
}

/// Global modifier to yield by type
int CvBuildingEntry::GetGlobalYieldModifier(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piGlobalYieldModifier ? m_piGlobalYieldModifier[i] : -1;
}

/// Array of global yield modifiers
int* CvBuildingEntry::GetGlobalYieldModifierArray() const
{
	return m_piGlobalYieldModifier;
}

/// Change to yield based on earning a tech
int CvBuildingEntry::GetTechEnhancedYieldChange(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piTechEnhancedYieldChange ? m_piTechEnhancedYieldChange[i] : -1;
}

/// Array of yield changes based on earning a tech
int* CvBuildingEntry::GetTechEnhancedYieldChangeArray() const
{
	return m_piTechEnhancedYieldChange;
}

/// Sea plot yield changes by type
int CvBuildingEntry::GetSeaPlotYieldChange(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piSeaPlotYieldChange ? m_piSeaPlotYieldChange[i] : -1;
}

/// Array of sea plot yield changes
int* CvBuildingEntry::GetSeaPlotYieldChangeArray() const
{
	return m_piSeaPlotYieldChange;
}

/// River plot yield changes by type
int CvBuildingEntry::GetRiverPlotYieldChange(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piRiverPlotYieldChange ? m_piRiverPlotYieldChange[i] : -1;
}

/// Array of river plot yield changes
int* CvBuildingEntry::GetRiverPlotYieldChangeArray() const
{
	return m_piRiverPlotYieldChange;
}

/// Global River plot yield changes by type
int CvBuildingEntry::GetRiverPlotYieldChangeGlobal(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piRiverPlotYieldChangeGlobal ? m_piRiverPlotYieldChangeGlobal[i] : -1;
}

/// Array of Global river plot yield changes
int* CvBuildingEntry::GetRiverPlotYieldChangeGlobalArray() const
{
	return m_piRiverPlotYieldChangeGlobal;
}

/// Lake plot yield changes by type
int CvBuildingEntry::GetLakePlotYieldChange(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piLakePlotYieldChange ? m_piLakePlotYieldChange[i] : -1;
}

/// Array of lake plot yield changes
int* CvBuildingEntry::GetLakePlotYieldChangeArray() const
{
	return m_piLakePlotYieldChange;
}

/// Sea resource yield changes by type
int CvBuildingEntry::GetSeaResourceYieldChange(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piSeaResourceYieldChange ? m_piSeaResourceYieldChange[i] : -1;
}

/// Array of sea resource yield changes
int* CvBuildingEntry::GetSeaResourceYieldChangeArray() const
{
	return m_piSeaResourceYieldChange;
}

/// Free combat experience by unit combat type
int CvBuildingEntry::GetUnitCombatFreeExperience(int i) const
{
	CvAssertMsg(i < GC.getNumUnitCombatClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piUnitCombatFreeExperience ? m_piUnitCombatFreeExperience[i] : -1;
}

/// Free combat experience by unit combat type
int CvBuildingEntry::GetUnitCombatProductionModifier(int i) const
{
	CvAssertMsg(i < GC.getNumUnitCombatClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piUnitCombatProductionModifiers ? m_piUnitCombatProductionModifiers[i] : -1;
}

/// Free experience gained for units in this domain
int CvBuildingEntry::GetDomainFreeExperience(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainFreeExperience ? m_piDomainFreeExperience[i] : -1;
}

/// Free experience gained for units in this domain for each Great Work in this building
int CvBuildingEntry::GetDomainFreeExperiencePerGreatWork(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainFreeExperiencePerGreatWork ? m_piDomainFreeExperiencePerGreatWork[i] : -1;
}

/// Free experience gained for units in this domain from pops
int CvBuildingEntry::GetDomainFreeExperiencesPerPop(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainFreeExperiencesPerPop ? m_piDomainFreeExperiencesPerPop[i] : -1;
}

int CvBuildingEntry::GetDomainFreeExperiencesPerPopGlobal(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainFreeExperiencesPerPopGlobal ? m_piDomainFreeExperiencesPerPopGlobal[i] : -1;
}

/// Free experience unit gained when doturn
int CvBuildingEntry::GetDomainFreeExperiencesPerTurn(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainFreeExperiencesPerTurn ? m_piDomainFreeExperiencesPerTurn[i] : -1;
}

int CvBuildingEntry::GetDomainFreeExperiencesPerTurnGlobal(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainFreeExperiencesPerTurnGlobal ? m_piDomainFreeExperiencesPerTurnGlobal[i] : -1;
}

/// Enemy combat punishment from this building
int CvBuildingEntry::GetDomainEnemyCombatModifier(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainEnemyCombatModifier ? m_piDomainEnemyCombatModifier[i] : -1;
}

int CvBuildingEntry::GetDomainEnemyCombatModifierGlobal(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainEnemyCombatModifierGlobal ? m_piDomainEnemyCombatModifierGlobal[i] : -1;
}

/// Our units' combat bonus in this city from this building
int CvBuildingEntry::GetDomainFriendsCombatModifierLocal(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainFriendsCombatModifierLocal ? m_piDomainFriendsCombatModifierLocal[i] : -1;
}

#if defined(MOD_ROG_CORE)
/// Free experience gained for units in this domain for each Great Work in this building
int CvBuildingEntry::GetDomainFreeExperiencePerGreatWorkGlobal(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainFreeExperiencePerGreatWorkGlobal ? m_piDomainFreeExperiencePerGreatWorkGlobal[i] : -1;
}

/// Free experience gained for units in this domain (global)
int CvBuildingEntry::GetDomainFreeExperienceGlobal(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	std::map<int, int>::const_iterator it = m_piDomainFreeExperienceGlobal.find(i);
	if (it != m_piDomainFreeExperienceGlobal.end()) // find returns the iterator to map::end if the key i is not present in the map
	{
		return it->second;
	}
	return 0;
}

int CvBuildingEntry::GetUnitTypePrmoteHealGlobal(int i) const
{
	CvAssertMsg(i < GC.getNumUnitInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	std::map<int, int>::const_iterator it = m_piUnitTypePrmoteHealGlobal.find(i);
	if (it != m_piUnitTypePrmoteHealGlobal.end()) // find returns the iterator to map::end if the key i is not present in the map
	{
		return it->second;
	}
	return 0;
}
#endif

#if defined(MOD_TROOPS_AND_CROPS_FOR_SP)
int CvBuildingEntry::GetDomainTroops(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainTroops ? m_piDomainTroops[i] : -1;
}
#endif

/// Production modifier in this domain
int CvBuildingEntry::GetDomainProductionModifier(int i) const
{
	CvAssertMsg(i < NUM_DOMAIN_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piDomainProductionModifier ? m_piDomainProductionModifier[i] : -1;
}

/// Resources consumed to construct
int CvBuildingEntry::GetResourceQuantityRequirement(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piResourceQuantityRequirements ? m_piResourceQuantityRequirements[i] : -1;
}

/// Resources provided once constructed
int CvBuildingEntry::GetResourceQuantity(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piResourceQuantity ? m_piResourceQuantity[i] : -1;
}

/// Boost in Culture for each of these Resources
int CvBuildingEntry::GetResourceCultureChange(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piResourceCultureChanges ? m_piResourceCultureChanges[i] : -1;
}

/// Boost in Faith for each of these Resources
int CvBuildingEntry::GetResourceFaithChange(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piResourceFaithChanges ? m_piResourceFaithChanges[i] : -1;
}

/// Boost in production for leader with this trait
int CvBuildingEntry::GetProductionTraits(int i) const
{
	CvAssertMsg(i < GC.getNumTraitInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piProductionTraits ? m_piProductionTraits[i] : 0;
}

/// Number of prerequisite buildings of a particular class
int CvBuildingEntry::GetPrereqNumOfBuildingClass(int i) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piPrereqNumOfBuildingClass ? m_piPrereqNumOfBuildingClass[i] : -1;
}

/// Find value of flavors associated with this building
int CvBuildingEntry::GetFlavorValue(int i) const
{
	CvAssertMsg(i < GC.getNumFlavorTypes(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piFlavorValue ? m_piFlavorValue[i] : 0;
}

/// Prerequisite Buildings with OR
const std::vector<int>& CvBuildingEntry::GetLockedByBuildings() const
{
	return m_piLockedByBuildings;
}
/// Prerequisite techs with AND
const std::vector<int>& CvBuildingEntry::GetPrereqAndTechs() const
{
	return m_piPrereqAndTechs;
}
/// Prerequisite resources with AND
const std::vector<int>& CvBuildingEntry::GetLocalResourceAnd() const
{
	return m_piLocalResourceAnds;
}
/// Prerequisite resources with OR
const std::vector<int>& CvBuildingEntry::GetLocalResourceOr() const
{
	return m_piLocalResourceOrs;
}
/// Prerequisite Feature with AND
const std::vector<int>& CvBuildingEntry::GetEmpireResourceAnd() const
{
	return m_piEmpireResourceAnds;
}
/// Prerequisite resources with OR
const std::vector<int>& CvBuildingEntry::GetEmpireResourceOr() const
{
	return m_piEmpireResourceOrs;
}
/// Prerequisite Feature with AND
const std::vector<int>& CvBuildingEntry::GetFeatureAnd() const
{
	return m_piLocalFeatureAnds;
}
/// Prerequisite Feature with OR
const std::vector<int>& CvBuildingEntry::GetFeatureOr() const
{
	return m_piLocalFeatureOrs;
}
/// Prerequisite Plot with AND
const std::vector<int>& CvBuildingEntry::GetPlotAnd() const
{
	return m_piLocalPlotAnds;
}

/// Modifier to Hurry cost
int CvBuildingEntry::GetHurryModifier(int i) const
{
	CvAssertMsg(i < GC.getNumHurryInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_paiHurryModifier ? m_paiHurryModifier[i] : -1;
}

/// Modifier to Hurry cost local
int CvBuildingEntry::GetHurryModifierLocal(int i) const
{
	CvAssertMsg(i < GC.getNumHurryInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_paiHurryModifierLocal ? m_paiHurryModifierLocal[i] : -1;
}

#if defined(MOD_GLOBAL_BUILDING_INSTANT_YIELD)
/// Instant yield
int CvBuildingEntry::GetInstantYield(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piInstantYield ? m_piInstantYield[i] : 0;
}

/// Array of instant yields
int* CvBuildingEntry::GetInstantYieldArray() const
{
	return m_piInstantYield;
}
/// Array of instant yields
bool CvBuildingEntry::IsAllowInstantYield() const
{
	return m_iInstantYieldCount > 0;
}
#endif

// Resource provided by Population
int CvBuildingEntry::GetResourceQuantityFromPOP(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piResourceQuantityFromPOP ? m_piResourceQuantityFromPOP[i] : -1;
}

int CvBuildingEntry::GetYieldPerFriend(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldPerFriend ? m_piYieldPerFriend[i] : -1;
}

int CvBuildingEntry::GetYieldPerAlly(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldPerAlly ? m_piYieldPerAlly[i] : -1;
}

int CvBuildingEntry::GetYieldPerEspionageSpy(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldPerEspionageSpy ? m_piYieldPerEspionageSpy[i] : -1;
}

int CvBuildingEntry::GetYieldChangeWorldWonder(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangeWorldWonder ? m_piYieldChangeWorldWonder[i] : 0;
}
int CvBuildingEntry::GetYieldChangeWorldWonderGlobal(int i) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_piYieldChangeWorldWonderGlobal ? m_piYieldChangeWorldWonderGlobal[i] : 0;
}


/// Change to Improvement yield by type
int CvBuildingEntry::GetImprovementYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumImprovementInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiImprovementYieldChange ? m_ppaiImprovementYieldChange[i][j] : -1;
}

/// Array of changes to Improvement yield
int* CvBuildingEntry::GetImprovementYieldChangeArray(int i) const
{
	CvAssertMsg(i < GC.getNumImprovementInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiImprovementYieldChange[i];
}



/// Change to Improvement yield by type
int CvBuildingEntry::GetImprovementYieldChangeGlobal(int i, int j) const
{
	CvAssertMsg(i < GC.getNumImprovementInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiImprovementYieldChangeGlobal ? m_ppaiImprovementYieldChangeGlobal[i][j] : -1;
}

/// Array of changes to Improvement yield
int* CvBuildingEntry::GetImprovementYieldChangeGlobalArray(int i) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	//CvAssertMsg(i < GC.getNumImprovementInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiImprovementYieldChangeGlobal[i];
}


/// Change to Improvement yield by type
int CvBuildingEntry::GetFeatureYieldChangesGlobal(int i, int j) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiFeatureYieldChangesGlobal[i][j];  
}


int CvBuildingEntry::GetTerrainYieldChangesGlobal(int i, int j) const
{
	CvAssertMsg(i < GC.getNumTerrainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiTerrainYieldChangesGlobal[i][j];
}

/// Change to Terrain yield by type
int CvBuildingEntry::GetYieldPerXTerrain(int i, int j) const
{
	CvAssertMsg(i < GC.getNumTerrainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiYieldPerXTerrain ? m_ppaiYieldPerXTerrain[i][j] : -1;
}

/// Array of changes to Feature yield
int* CvBuildingEntry::GetYieldPerXTerrainArray(int i) const
{
	CvAssertMsg(i < GC.getNumTerrainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiYieldPerXTerrain[i];
}

int CvBuildingEntry::GetYieldPerXFeature(int i, int j) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiYieldPerXFeature ? m_ppaiYieldPerXFeature[i][j] : -1;
}

/// Array of changes to Feature yield
int* CvBuildingEntry::GetYieldPerXFeatureArray(int i) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiYieldPerXFeature[i];
}


/// Change to specialist yield by type
int CvBuildingEntry::GetSpecialistYieldChangeLocal(int i, int j) const
{
	CvAssertMsg(i < GC.getNumSpecialistInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiSpecialistYieldChangeLocal ? m_ppaiSpecialistYieldChangeLocal[i][j] : -1;
}
/// Array of changes to specialist yield
int* CvBuildingEntry::GetSpecialistYieldChangeLocalArray(int i) const
{
	CvAssertMsg(i < GC.getNumSpecialistInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiSpecialistYieldChangeLocal[i];
}

/// Change to Resource yield by type
int CvBuildingEntry::GetResourceYieldChangeGlobal(int iResource, int iYieldType) const
{
	CvAssertMsg(iResource < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(iResource > -1, "Index out of bounds");
	CvAssertMsg(iYieldType < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(iYieldType > -1, "Index out of bounds");
	std::map<int, std::map<int, int>>::const_iterator itResource = m_ppiResourceYieldChangeGlobal.find(iResource);
	if (itResource != m_ppiResourceYieldChangeGlobal.end()) // find returns the iterator to map::end if the key iResource is not present in the map
	{
		std::map<int, int>::const_iterator itYield = itResource->second.find(iYieldType);
		if (itYield != itResource->second.end()) // find returns the iterator to map::end if the key iYield is not present in the map
		{
			return itYield->second;
		}
	}

	return 0;
}


/// Yield change for a specific BuildingClass by yield type
int CvBuildingEntry::GetBuildingClassYieldModifier(int i, int j) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiBuildingClassYieldModifiers[i][j];
}

/// Yield change for a specific BuildingClass by yield type
int CvBuildingEntry::GetBuildingClassLocalYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiBuildingClassLocalYieldChanges[i][j];
}

#if defined(MOD_ROG_CORE)

int CvBuildingEntry::GetSpecificGreatPersonRateModifier(int i) const
{
	CvAssertMsg(i < GC.getNumSpecialistInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_paiSpecificGreatPersonRateModifier ? m_paiSpecificGreatPersonRateModifier[i] : -1;
}

#endif

/// Can it only built if there is a building of this class in the city?
const std::vector<int>& CvBuildingEntry::GetBuildingClassesNeededInCity() const
{
	return m_setBuildingClassesNeededInCity;
}
/// Can it only built if there is a building of this class Global?
const std::vector<int>& CvBuildingEntry::GetBuildingClassesNeededGlobal() const
{
	return m_setBuildingClassesNeededGlobal;
}
/// Can it only built if there is a building in the city?
const std::vector<int>& CvBuildingEntry::GetBuildingsNeededInCity() const
{
	return m_setBuildingsNeededInCity;
}
/// Can it only built if there is a building Global?
const std::vector<int>& CvBuildingEntry::GetBuildingsNeededGlobal() const
{
	return m_setBuildingsNeededGlobal;
}

#if defined(MOD_BUILDING_NEW_EFFECT_FOR_SP)
int CvBuildingEntry::GetCityDefenseModifierGlobal() const
{
	return m_iCityDefenseModifierGlobal;
}

int CvBuildingEntry::GetUnitMaxExperienceLocal() const
{
	return m_iUnitMaxExperienceLocal;
}

int CvBuildingEntry::GetExtraSellRefund() const
{
	return m_iExtraSellRefund;
}

int CvBuildingEntry::GetExtraSellRefundModifierPerEra() const
{
	return m_iExtraSellRefundModifierPerEra;
}

int CvBuildingEntry::GetMinNumReligions() const
{
	return m_iMinNumReligions;
}

int CvBuildingEntry::GetLandmarksTourismPercentGlobal() const
{
	return m_iLandmarksTourismPercentGlobal;
}

int CvBuildingEntry::GetGreatWorksTourismModifierGlobal() const
{
	return m_iGreatWorksTourismModifierGlobal;
}

int CvBuildingEntry::GetTradeRouteSeaGoldBonusGlobal() const
{
	return m_iTradeRouteSeaGoldBonusGlobal;
}

int CvBuildingEntry::GetTradeRouteLandGoldBonusGlobal() const
{
	return m_iTradeRouteLandGoldBonusGlobal;
}

bool CvBuildingEntry::IsAnyWater() const
{
	return m_bAnyWater;
}
bool CvBuildingEntry::IsRiverOrCoastal() const
{
	return m_bRiverOrCoastal;
}
#endif

/// Free units which appear near city
int CvBuildingEntry::GetNumFreeUnit() const
{
	return m_iNumFreeUnit;
}
int CvBuildingEntry::GetNumFreeUnitTotal() const
{
	return m_iNumFreeUnitTotal;
}
std::pair<UnitTypes, int>* CvBuildingEntry::GetFreeUnits() const
{
	return m_pFreeUnits;
}


/// Does this building generate yields from other yields globally?
int CvBuildingEntry::GetYieldFromYieldGlobal(int i, int j) const
{
	CvAssertMsg(i < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");

	if (m_paYieldFromYieldGlobal == NULL || m_paYieldFromYieldGlobal[0].GetValue() == 0)
	{
		return 0;
	}
	else
	{
		for (int iI = 0; iI < NUM_YIELD_TYPES; iI++)
		{
			for (int iK = 0; iK < NUM_YIELD_TYPES; iK++)
			{
				if (m_paYieldFromYieldGlobal[iI].GetYieldIn() != i)
					continue;
				if (m_paYieldFromYieldGlobal[iI].GetYieldOut() != j)
					continue;

				return m_paYieldFromYieldGlobal[iI].GetValue();
			}
		}
	}

	return 0;
}

/// Change to Resource yield by type
int CvBuildingEntry::GetResourceYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiResourceYieldChange ? m_ppaiResourceYieldChange[i][j] : -1;
}

/// Array of changes to Resource yield
int* CvBuildingEntry::GetResourceYieldChangeArray(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiResourceYieldChange[i];
}

/// Change to Feature yield by type
int CvBuildingEntry::GetFeatureYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiFeatureYieldChange ? m_ppaiFeatureYieldChange[i][j] : -1;
}

/// Array of changes to Feature yield
int* CvBuildingEntry::GetFeatureYieldChangeArray(int i) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiFeatureYieldChange[i];
}


/// Change to Terrain yield by type
int CvBuildingEntry::GetTerrainYieldModifier(int i, int j) const
{
	CvAssertMsg(i < GC.getNumTerrainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiTerrainYieldModifier ? m_ppaiTerrainYieldModifier[i][j] : -1;
}

/// Array of changes to Feature yield
int* CvBuildingEntry::GetTerrainYieldModifierArray(int i) const
{
	CvAssertMsg(i < GC.getNumTerrainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiTerrainYieldModifier[i];
}


/// Change to specialist yield by type
int CvBuildingEntry::GetSpecialistYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumSpecialistInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiSpecialistYieldChange ? m_ppaiSpecialistYieldChange[i][j] : -1;
}

/// Array of changes to specialist yield
int* CvBuildingEntry::GetSpecialistYieldChangeArray(int i) const
{
	CvAssertMsg(i < GC.getNumSpecialistInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiSpecialistYieldChange[i];
}


/// Modifier to Improvement yield
int CvBuildingEntry::GetImprovementYieldModifier(int i, int j) const
{
	CvAssertMsg(i < GC.getNumImprovementInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiImprovementYieldModifier ? m_ppaiImprovementYieldModifier[i][j] : -1;
}

/// Array of modifiers to Improvement yield
int* CvBuildingEntry::GetImprovementYieldModifierArray(int i) const
{
	CvAssertMsg(i < GC.getNumImprovementInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiImprovementYieldModifier[i];
}


int CvBuildingEntry::GetSpecialistYieldModifier(int i, int j) const
{
	CvAssertMsg(i < GC.getNumSpecialistInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiSpecialistYieldModifier ? m_ppaiSpecialistYieldModifier[i][j] : -1;
}

/// Array of modifiers to Improvement yield
int* CvBuildingEntry::GetSpecialistYieldModifierArray(int i) const
{
	CvAssertMsg(i < GC.getNumSpecialistInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiSpecialistYieldModifier[i];
}

int CvBuildingEntry::GetSpecialistYieldModifierGlobal(int i, int j) const
{
	CvAssertMsg(i < GC.getNumSpecialistInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiSpecialistYieldModifierGlobal ? m_ppaiSpecialistYieldModifierGlobal[i][j] : -1;
}

/// Array of modifiers to Improvement yield
int* CvBuildingEntry::GetSpecialistYieldModifierGlobalArray(int i) const
{
	CvAssertMsg(i < GC.getNumSpecialistInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiSpecialistYieldModifierGlobal[i];
}


/// Modifier to Feature yield
int CvBuildingEntry::GetFeatureYieldModifier(int i, int j) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiFeatureYieldModifier ? m_ppaiFeatureYieldModifier[i][j] : -1;
}

/// Array of modifiers to Feature yield
int* CvBuildingEntry::GetFeatureYieldModifierArray(int i) const
{
	CvAssertMsg(i < GC.getNumFeatureInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiFeatureYieldModifier[i];
}

/// Modifier to resource yield
int CvBuildingEntry::GetResourceYieldModifier(int i, int j) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiResourceYieldModifier ? m_ppaiResourceYieldModifier[i][j] : -1;
}

/// Array of modifiers to resource yield
int* CvBuildingEntry::GetResourceYieldModifierArray(int i) const
{
	CvAssertMsg(i < GC.getNumResourceInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiResourceYieldModifier[i];
}

/// Change to Terrain yield by type
int CvBuildingEntry::GetTerrainYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumTerrainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppaiTerrainYieldChange ? m_ppaiTerrainYieldChange[i][j] : -1;
}

/// Array of changes to Feature yield
int* CvBuildingEntry::GetTerrainYieldChangeArray(int i) const
{
	CvAssertMsg(i < GC.getNumTerrainInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiTerrainYieldChange[i];
}

#if defined(MOD_API_UNIFIED_YIELDS) && defined(MOD_API_PLOT_YIELDS)
/// Change to Plot yield by type
int CvBuildingEntry::GetPlotYieldChange(int i, int j) const
{
	if (MOD_API_PLOT_YIELDS) {
		CvAssertMsg(i < GC.getNumPlotInfos(), "Index out of bounds");
		CvAssertMsg(i > -1, "Index out of bounds");
		CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
		CvAssertMsg(j > -1, "Index out of bounds");
		return m_ppaiPlotYieldChange ? m_ppaiPlotYieldChange[i][j] : -1;
	} else {
		return 0;
	}
}

/// Array of changes to Plot yield
int* CvBuildingEntry::GetPlotYieldChangeArray(int i) const
{
	CvAssertMsg(i < GC.getNumPlotInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_ppaiPlotYieldChange[i];
}
#endif

/// Yield change for a specific BuildingClass by yield type
int CvBuildingEntry::GetBuildingClassYieldChange(int i, int j) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	CvAssertMsg(j < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(j > -1, "Index out of bounds");
	return m_ppiBuildingClassYieldChanges[i][j];
}

/// Amount of extra Happiness per turn a BuildingClass provides
int CvBuildingEntry::GetBuildingClassHappiness(int i) const
{
	CvAssertMsg(i < GC.getNumBuildingClassInfos(), "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");
	return m_paiBuildingClassHappiness ? m_paiBuildingClassHappiness[i] : -1;
}

#if defined(MOD_BUILDING_IMPROVEMENT_RESOURCES)
std::multimap<int, std::pair<int, int>> CvBuildingEntry::GetResourceFromImprovementArray() const
{
	return m_piiResourceFromImprovement;
}
#endif

CvThemingBonusInfo *CvBuildingEntry::GetThemingBonusInfo(int i) const
{
	CvAssertMsg(i < MAX_THEMING_BONUSES, "Index out of bounds");
	CvAssertMsg(i > -1, "Index out of bounds");

	if (m_paThemingBonusInfo[0].m_iBonus == 0)
	{
		return NULL;
	}
	else
	{
		return &m_paThemingBonusInfo[i];
	}
}

#ifdef MOD_API_BUILDING_ENABLE_PURCHASE_UNITS
int CvBuildingEntry::GetNumAllowPurchaseUnitsByYieldType(YieldTypes iType) {
	CvAssertMsg(iType < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(iType > -1, "Index out of bounds");
	return m_iNumAllowPurchaseUnits[iType];
}

#ifdef MOD_BUILDINGS_YIELD_FROM_OTHER_YIELD
int CvBuildingEntry::GetYieldFromOtherYield(const YieldTypes eInType, const YieldTypes eOutType, const YieldFromYield eConvertType) const
{
	VALIDATE_OBJECT
		CvAssertMsg(eInType >= 0, "eInType expected to be >= 0");
	CvAssertMsg(eInType < NUM_YIELD_TYPES, "eInType expected to be < NUM_YIELD_TYPES");
	CvAssertMsg(eOutType >= 0, "eInType expected to be >= 0");
	CvAssertMsg(eOutType < NUM_YIELD_TYPES, "eInType expected to be < NUM_YIELD_TYPES");
	CvAssertMsg(eConvertType < YieldFromYield::LENGTH&& eConvertType >= 0, "eConvertType expected to be < YieldFromYield::LENGTH");

	return m_ppiYieldFromOtherYield[eOutType][eInType][eConvertType];
}

bool CvBuildingEntry::HasYieldFromOtherYield() const
{
	return m_bHasYieldFromOtherYield;
}

#endif

#ifdef MOD_GLOBAL_CITY_SCALES
CityScaleTypes CvBuildingEntry::GetEnableCityScaleGrowth() const
{
	return m_eEnableCityScaleGrowth;
}
bool CvBuildingEntry::GetEnableAllCityScaleGrowth() const
{
	return m_bEnableAllCityScaleGrowth;
}
#endif

std::pair<UnitClassTypes, int>* CvBuildingEntry::GetAllowPurchaseUnitsByYieldType(YieldTypes iType) {
	CvAssertMsg(iType < NUM_YIELD_TYPES, "Index out of bounds");
	CvAssertMsg(iType > -1, "Index out of bounds");
	return m_piAllowPurchaseUnits[iType];
}
#endif

#ifdef MOD_BUILDINGS_GOLDEN_AGE_EXTEND
int CvBuildingEntry::GetGoldenAgeUnitCombatModifier() const
{
	return this->m_iGoldenAgeUnitCombatModifier;
}
int CvBuildingEntry::GetGoldenAgeMeterMod() const
{
	return this->m_iGoldenAgeMeterMod;
}
#endif

int CvBuildingEntry::GetTradeRouteFromTheCityYields(YieldTypes eYieldTypes) const
{
	if (eYieldTypes < 0 || eYieldTypes >= NUM_YIELD_TYPES)
	{
		return 0;
	}

	return m_aTradeRouteFromTheCityYields[eYieldTypes];
}

int CvBuildingEntry::GetTradeRouteFromTheCityYieldsPerEra(YieldTypes eYieldTypes) const
{
	if (eYieldTypes < 0 || eYieldTypes >= NUM_YIELD_TYPES)
	{
		return 0;
	}

	return m_aTradeRouteFromTheCityYieldsPerEra[eYieldTypes];
}

//This building can only be built in capital
bool CvBuildingEntry::IsCapitalOnly() const
{
	return m_bCapitalOnly;
}

//This building can only be built in original capital city
bool CvBuildingEntry::IsOriginalCapitalOnly() const
{
	return m_bOriginalCapitalOnly;
}


//=====================================
// CvBuildingXMLEntries
//=====================================
/// Constructor
CvBuildingXMLEntries::CvBuildingXMLEntries(void)
{

}

/// Destructor
CvBuildingXMLEntries::~CvBuildingXMLEntries(void)
{
	DeleteArray();
}

/// Returns vector of policy entries
std::vector<CvBuildingEntry*>& CvBuildingXMLEntries::GetBuildingEntries()
{
	return m_paBuildingEntries;
}

/// Number of defined policies
int CvBuildingXMLEntries::GetNumBuildings()
{
	return m_paBuildingEntries.size();
}

/// Clear policy entries
void CvBuildingXMLEntries::DeleteArray()
{
	for(std::vector<CvBuildingEntry*>::iterator it = m_paBuildingEntries.begin(); it != m_paBuildingEntries.end(); ++it)
	{
		SAFE_DELETE(*it);
	}

	m_paBuildingEntries.clear();
}

/// Get a specific entry
CvBuildingEntry* CvBuildingXMLEntries::GetEntry(int index)
{
	if (index < 0) return nullptr;
	return m_paBuildingEntries[index];
}

//=====================================
// CvCityBuildings
//=====================================
/// Constructor
CvCityBuildings::CvCityBuildings():
	m_paiBuildingProduction(NULL),
	m_paiBuildingProductionTime(NULL),
	m_paiBuildingOriginalOwner(NULL),
	m_paiBuildingOriginalTime(NULL),
	m_paiNumRealBuilding(NULL),
	m_paiNumFreeBuilding(NULL),
	m_iNumBuildings(0),
	m_iBuildingProductionModifier(0),
	m_iBuildingDefense(0),
	m_iBuildingDefenseMod(0),
	m_iMissionaryExtraSpreads(0),
	m_iLandmarksTourismPercent(0),
	m_iGreatWorksTourismModifier(0),
	m_iNumBuildingsFromFaith(0),
	m_bSoldBuildingThisTurn(false),
	m_pBuildings(NULL),
	m_pCity(NULL)
{
}

/// Destructor
CvCityBuildings::~CvCityBuildings(void)
{
}

/// Initialize
void CvCityBuildings::Init(CvBuildingXMLEntries* pBuildings, CvCity* pCity)
{
	// Store off the pointers to objects we'll need later
	m_pBuildings = pBuildings;
	m_pCity = pCity;

	// Initialize status arrays

	int iNumBuildings = m_pBuildings->GetNumBuildings();

	CvAssertMsg((0 < iNumBuildings),  "m_pBuildings->GetNumBuildings() is not greater than zero but an array is being allocated in CvCityBuildings::Init");

	CvAssertMsg(m_paiBuildingProduction==NULL, "about to leak memory, CvCityBuildings::m_paiBuildingProduction");
	m_paiBuildingProduction = FNEW(int[iNumBuildings], c_eCiv5GameplayDLL, 0);

	CvAssertMsg(m_paiBuildingProductionTime==NULL, "about to leak memory, CvCityBuildings::m_paiBuildingProductionTime");
	m_paiBuildingProductionTime = FNEW(int[iNumBuildings], c_eCiv5GameplayDLL, 0);

	CvAssertMsg(m_paiBuildingOriginalOwner==NULL, "about to leak memory, CvCityBuildings::m_paiBuildingOriginalOwner");
	m_paiBuildingOriginalOwner = FNEW(int[iNumBuildings], c_eCiv5GameplayDLL, 0);

	CvAssertMsg(m_paiBuildingOriginalTime==NULL, "about to leak memory, CvCityBuildings::m_paiBuildingOriginalTime");
	m_paiBuildingOriginalTime = FNEW(int[iNumBuildings], c_eCiv5GameplayDLL, 0);

	CvAssertMsg(m_paiNumRealBuilding==NULL, "about to leak memory, CvCityBuildings::m_paiNumRealBuilding");
	m_paiNumRealBuilding = FNEW(int[iNumBuildings], c_eCiv5GameplayDLL, 0);

	CvAssertMsg(m_paiNumFreeBuilding==NULL, "about to leak memory, CvCityBuildings::m_paiNumFreeBuilding");
	m_paiNumFreeBuilding = FNEW(int[iNumBuildings], c_eCiv5GameplayDLL, 0);

	m_aBuildingYieldChange.clear();
	m_aBuildingGreatWork.clear();

	Reset();
}

/// Deallocate memory created in initialize
void CvCityBuildings::Uninit()
{
	SAFE_DELETE_ARRAY(m_paiBuildingProduction);
	SAFE_DELETE_ARRAY(m_paiBuildingProductionTime);
	SAFE_DELETE_ARRAY(m_paiBuildingOriginalOwner);
	SAFE_DELETE_ARRAY(m_paiBuildingOriginalTime);
	SAFE_DELETE_ARRAY(m_paiNumRealBuilding);
	SAFE_DELETE_ARRAY(m_paiNumFreeBuilding);
}

/// Reset status arrays to all false
void CvCityBuildings::Reset()
{
	int iI;

	// Initialize non-arrays
	m_iNumBuildings = 0;
	m_iBuildingProductionModifier = 0;
	m_iBuildingDefense = 0;
	m_iBuildingDefenseMod = 0;
	m_iMissionaryExtraSpreads = 0;
	m_iLandmarksTourismPercent = 0;
	m_iGreatWorksTourismModifier = 0;
	m_iNumBuildingsFromFaith = 0;

	m_bSoldBuildingThisTurn = false;

	for(iI = 0; iI < m_pBuildings->GetNumBuildings(); iI++)
	{
		m_paiBuildingProduction[iI] = 0;
		m_paiBuildingProductionTime[iI] = 0;
		m_paiBuildingOriginalOwner[iI] = NO_PLAYER;
		m_paiBuildingOriginalTime[iI] = MIN_INT;
		m_paiNumRealBuilding[iI] = 0;
		m_paiNumFreeBuilding[iI] = 0;
	}
}

/// Serialization read
void CvCityBuildings::Read(FDataStream& kStream)
{
	CvAssertMsg(m_pBuildings != NULL && m_pBuildings->GetNumBuildings() > 0, "Number of buildings to serialize is expected to greater than 0");

	// Version number to maintain backwards compatibility
	uint uiVersion;
	kStream >> uiVersion;
	MOD_SERIALIZE_INIT_READ(kStream);

	kStream >> m_iNumBuildings;
	kStream >> m_iBuildingProductionModifier;
	kStream >> m_iBuildingDefense;
	kStream >> m_iBuildingDefenseMod;
	kStream >> m_iMissionaryExtraSpreads;
	kStream >> m_iLandmarksTourismPercent;
	kStream >> m_iGreatWorksTourismModifier;
	kStream >> m_iNumBuildingsFromFaith;

	kStream >> m_bSoldBuildingThisTurn;

	BuildingArrayHelpers::Read(kStream, m_paiBuildingProduction);
	BuildingArrayHelpers::Read(kStream, m_paiBuildingProductionTime);
	BuildingArrayHelpers::Read(kStream, m_paiBuildingOriginalOwner);
	BuildingArrayHelpers::Read(kStream, m_paiBuildingOriginalTime);
	BuildingArrayHelpers::Read(kStream, m_paiNumRealBuilding);
	BuildingArrayHelpers::Read(kStream, m_paiNumFreeBuilding);

	kStream >> m_aBuildingYieldChange;
	kStream >> m_aBuildingGreatWork;
}

/// Serialization write
void CvCityBuildings::Write(FDataStream& kStream)
{
	CvAssertMsg(m_pBuildings != NULL && m_pBuildings->GetNumBuildings() > 0, "Number of buildings to serialize is expected to greater than 0");

	// Current version number
	uint uiVersion = 1;
	kStream << uiVersion;
	MOD_SERIALIZE_INIT_WRITE(kStream);

	kStream << m_iNumBuildings;
	kStream << m_iBuildingProductionModifier;
	kStream << m_iBuildingDefense;
	kStream << m_iBuildingDefenseMod;
	kStream << m_iMissionaryExtraSpreads;
	kStream << m_iLandmarksTourismPercent;
	kStream << m_iGreatWorksTourismModifier;
	kStream << m_iNumBuildingsFromFaith;
	kStream << m_bSoldBuildingThisTurn;

#ifdef _MSC_VER
#pragma warning ( push )
#pragma warning ( disable : 6011 ) // if m_pBuildings is NULL during load, we're screwed. Redesign the class or the loader code.
#endif//_MSC_VER
	int iNumBuildings = m_pBuildings->GetNumBuildings();
#ifdef _MSC_VER
#pragma warning ( pop )
#endif//_MSC_VER

	BuildingArrayHelpers::Write(kStream, m_paiBuildingProduction, iNumBuildings);
	BuildingArrayHelpers::Write(kStream, m_paiBuildingProductionTime, iNumBuildings);
	BuildingArrayHelpers::Write(kStream, m_paiBuildingOriginalOwner, iNumBuildings);
	BuildingArrayHelpers::Write(kStream, m_paiBuildingOriginalTime, iNumBuildings);
	BuildingArrayHelpers::Write(kStream, m_paiNumRealBuilding, iNumBuildings);
	BuildingArrayHelpers::Write(kStream, m_paiNumFreeBuilding, iNumBuildings);

	kStream << m_aBuildingYieldChange;
	kStream << m_aBuildingGreatWork;
}

/// Accessor: Get full array of all building XML data
CvBuildingXMLEntries* CvCityBuildings::GetBuildings() const
{
	return m_pBuildings;
}

/// Accessor: Total number of buildings in the city
int CvCityBuildings::GetNumBuildings() const
{
	return m_iNumBuildings;
}

/// Accessor: Update total number of buildings in the city
void CvCityBuildings::ChangeNumBuildings(int iChange)
{
	m_iNumBuildings = (m_iNumBuildings + iChange);
	CvAssert(GetNumBuildings() >= 0);

//	GET_PLAYER(m_pCity->getOwner()).updateNumResourceUsed();
}

/// Accessor: How many of these buildings in the city?
int CvCityBuildings::GetNumBuilding(BuildingTypes eIndex) const
{
	CvAssertMsg(eIndex != NO_BUILDING, "BuildingType eIndex is expected to not be NO_BUILDING");

	if(GC.getCITY_MAX_NUM_BUILDINGS() <= 1)
	{
		return std::max(GetNumRealBuilding(eIndex), GetNumFreeBuilding(eIndex));
	}
	else
	{
		return (GetNumRealBuilding(eIndex) + GetNumFreeBuilding(eIndex));
	}
}

/// Accessor: How many of these buildings are not obsolete?
int CvCityBuildings::GetNumActiveBuilding(BuildingTypes eIndex) const
{
	CvAssertMsg(eIndex != NO_BUILDING, "BuildingType eIndex is expected to not be NO_BUILDING");

	if(GET_TEAM(m_pCity->getTeam()).isObsoleteBuilding(eIndex))
	{
		return 0;
	}

	return (GetNumBuilding(eIndex));
}

/// Is the player allowed to sell building eIndex in this city?
bool CvCityBuildings::IsBuildingSellable(const CvBuildingEntry& kBuilding) const
{
	// Can't sell more than one building per turn
	if(IsSoldBuildingThisTurn())
		return false;

	// Can't sell a building if it doesn't cost us anything (no exploits)
	if(kBuilding.GetGoldMaintenance() <= 0)
		return false;

	// Is this a free building?
	if(GetNumFreeBuilding((BuildingTypes)kBuilding.GetID()) > 0)
		return false;

	// Science building in capital that has given us a tech boost?
	if(m_pCity->isCapital() && kBuilding.IsScienceBuilding())
	{
		return !(GET_PLAYER(m_pCity->getOwner()).GetPlayerTraits()->IsTechBoostFromCapitalScienceBuildings());
	}

	// Great Work present in this one?
	const BuildingClassTypes buildingClassType = (BuildingClassTypes) kBuilding.GetBuildingClassType();
	if (IsHoldingGreatWork(buildingClassType))
	{
		return false;
	}

	ICvEngineScriptSystem1* pkScriptSystem = gDLL->GetScriptSystem();
	if(pkScriptSystem)
	{
		CvLuaArgsHandle args;
		args->Push(m_pCity->getOwner());
		args->Push(kBuilding.GetID());

		// Attempt to execute the game events.
		// Will return false if there are no registered listeners.
		bool bResult = false;
		if(LuaSupport::CallTestAll(pkScriptSystem, "CityBuildingsIsBuildingSellable", args.get(), bResult))
		{
			// Check the result.
			if(bResult == false)
			{
				return false;
			}
		}
	}

	return true;
}

/// Sell eIndex~!
void CvCityBuildings::DoSellBuilding(BuildingTypes eIndex)
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");

	CvBuildingEntry* pkBuildingEntry = GC.getBuildingInfo(eIndex);
	if(!pkBuildingEntry)
		return;

	// Can we actually do this?
	if(!IsBuildingSellable(*pkBuildingEntry))
		return;

	// Gold refund
	int iRefund = GetSellBuildingRefund(eIndex);
	GET_PLAYER(m_pCity->getOwner()).GetTreasury()->ChangeGold(iRefund);

	// Kick everyone out
	m_pCity->GetCityCitizens()->DoRemoveAllSpecialistsFromBuilding(eIndex);

	SetNumRealBuilding(eIndex, 0);

	SetSoldBuildingThisTurn(true);
}

/// How much of a refund will the player get from selling eIndex?
int CvCityBuildings::GetSellBuildingRefund(BuildingTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");

	CvBuildingEntry* pkBuildingEntry = GC.getBuildingInfo(eIndex);
	if(!pkBuildingEntry) return 0;

	CvPlayerAI& pPlayer = GET_PLAYER(m_pCity->getOwner());

	int iRefund = 0;

	int iExtraSellRefund = pkBuildingEntry->GetExtraSellRefund();
	if(iExtraSellRefund != 0)
	{
		int iExtraModifier = pkBuildingEntry->GetExtraSellRefundModifierPerEra() *  pPlayer.GetCurrentEra() + 100;
		iExtraSellRefund *= iExtraModifier;
		iExtraSellRefund /= 100;
		iRefund += iExtraSellRefund;
	}
	else
	{
		iRefund += pPlayer.getProductionNeeded(eIndex);
		iRefund /= /*10*/ GC.getBUILDING_SALE_DIVISOR();
	}

	return iRefund;
}

/// Has a building already been sold this turn?
bool CvCityBuildings::IsSoldBuildingThisTurn() const
{
	return m_bSoldBuildingThisTurn;
}

/// Has a building already been sold this turn?
void CvCityBuildings::SetSoldBuildingThisTurn(bool bValue)
{
	if(IsSoldBuildingThisTurn() != bValue)
		m_bSoldBuildingThisTurn = bValue;
}

/// What is the total maintenance? (no modifiers)
int CvCityBuildings::GetTotalBaseBuildingMaintenance() const
{
	int iTotalCost = 0;

	for(int iBuildingLoop = 0; iBuildingLoop < GC.getNumBuildingInfos(); iBuildingLoop++)
	{
		const BuildingTypes eBuilding = static_cast<BuildingTypes>(iBuildingLoop);
		CvBuildingEntry* pkBuildingInfo = GC.getBuildingInfo(eBuilding);

		if(pkBuildingInfo)
		{
			if(GetNumBuilding(eBuilding))
				iTotalCost += (pkBuildingInfo->GetGoldMaintenance() * GetNumBuilding(eBuilding));
		}
	}

	for (int iProjectLoop = 0; iProjectLoop < GC.getNumProjectInfos(); iProjectLoop++)
	{
		const ProjectTypes eProject = static_cast<ProjectTypes>(iProjectLoop);
		CvProjectEntry* pkProject = GC.getProjectInfo(eProject);

		if (pkProject && pkProject->GetGoldMaintenance() > 0)
		{
			iTotalCost += (m_pCity->getProjectCount(eProject) * pkProject->GetGoldMaintenance());
		}
	}

	return iTotalCost;
}

/// Accessor: How far is construction of this building?
int CvCityBuildings::GetBuildingProduction(BuildingTypes eIndex)	const
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");
	return m_paiBuildingProduction[eIndex] / 100;
}

/// Accessor: How far is construction of this building? (in hundredths)
int CvCityBuildings::GetBuildingProductionTimes100(BuildingTypes eIndex)	const
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");
	return m_paiBuildingProduction[eIndex];
}

/// Accessor: Set how much construction is complete for this building
void CvCityBuildings::SetBuildingProduction(BuildingTypes eIndex, int iNewValue)
{
	SetBuildingProductionTimes100(eIndex, iNewValue*100);
}

/// Accessor: Set how much construction is complete for this building (in hundredths)
void CvCityBuildings::SetBuildingProductionTimes100(BuildingTypes eIndex, int iNewValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings())");

	if(GetBuildingProductionTimes100(eIndex) != iNewValue)
	{
		if(GetBuildingProductionTimes100(eIndex) == 0)
		{
			NotifyNewBuildingStarted(eIndex);
		}

		m_paiBuildingProduction[eIndex] = iNewValue;
		CvAssert(GetBuildingProductionTimes100(eIndex) >= 0);

		if((m_pCity->getOwner() == GC.getGame().getActivePlayer()) && m_pCity->isCitySelected())
		{
			GC.GetEngineUserInterface()->setDirty(CityScreen_DIRTY_BIT, true);
		}

		auto_ptr<ICvCity1> pCity = GC.WrapCityPointer(m_pCity);

		GC.GetEngineUserInterface()->SetSpecificCityInfoDirty(pCity.get(), CITY_UPDATE_TYPE_BANNER);
	}
}

/// Accessor: Update construction progress for this building
void CvCityBuildings::ChangeBuildingProduction(BuildingTypes eIndex, int iChange)
{
	ChangeBuildingProductionTimes100(eIndex, iChange*100);
}

/// Accessor: Update construction progress for this building (in hundredths)
void CvCityBuildings::ChangeBuildingProductionTimes100(BuildingTypes eIndex, int iChange)
{
	SetBuildingProductionTimes100(eIndex, (GetBuildingProductionTimes100(eIndex) + iChange));
}

/// Accessor: How many turns has this building been under production?
int CvCityBuildings::GetBuildingProductionTime(BuildingTypes eIndex)	const
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");
	return m_paiBuildingProductionTime[eIndex];
}

/// Accessor: Set number of turns this building been under production
void CvCityBuildings::SetBuildingProductionTime(BuildingTypes eIndex, int iNewValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");
	m_paiBuildingProductionTime[eIndex] = iNewValue;
	CvAssert(GetBuildingProductionTime(eIndex) >= 0);
}

/// Accessor: Change number of turns this building been under production
void CvCityBuildings::ChangeBuildingProductionTime(BuildingTypes eIndex, int iChange)
{
	SetBuildingProductionTime(eIndex, (GetBuildingProductionTime(eIndex) + iChange));
}

/// Accessor: Who owned the city when this building was built?
int CvCityBuildings::GetBuildingOriginalOwner(BuildingTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");
	return m_paiBuildingOriginalOwner[eIndex];
}

/// Accessor: Set who owned the city when this building was built
void CvCityBuildings::SetBuildingOriginalOwner(BuildingTypes eIndex, int iNewValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");
	m_paiBuildingOriginalOwner[eIndex] = iNewValue;
}

/// Accessor: What year was this building built?
int CvCityBuildings::GetBuildingOriginalTime(BuildingTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");
	return m_paiBuildingOriginalTime[eIndex];
}

/// Accessor: Set year building was built
void CvCityBuildings::SetBuildingOriginalTime(BuildingTypes eIndex, int iNewValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");
	m_paiBuildingOriginalTime[eIndex] = iNewValue;
}

/// Accessor: How many of these buildings have been constructed in the city?
int CvCityBuildings::GetNumRealBuilding(BuildingTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");
	return m_paiNumRealBuilding[eIndex];
}

/// Accessor: Set number of these buildings that have been constructed in the city
void CvCityBuildings::SetNumRealBuilding(BuildingTypes eIndex, int iNewValue)
{
	SetNumRealBuildingTimed(eIndex, iNewValue, true, m_pCity->getOwner(), GC.getGame().getGameTurnYear());

}

/// Accessor: Set number of these buildings that have been constructed in the city (with date)
void CvCityBuildings::SetNumRealBuildingTimed(BuildingTypes eIndex, int iNewValue, bool bFirst, PlayerTypes eOriginalOwner, int iOriginalTime)
{
	CvPlayer* pPlayer = &GET_PLAYER(m_pCity->getOwner());

	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");

	int iChangeNumRealBuilding = iNewValue - GetNumRealBuilding(eIndex);
	if (iChangeNumRealBuilding == 0)
	{
		return;
	}

	CvBuildingEntry* buildingEntry = GC.getBuildingInfo(eIndex);
	if (buildingEntry == nullptr)
	{
		return;
	}

	const BuildingClassTypes buildingClassType = (BuildingClassTypes) buildingEntry->GetBuildingClassType();
	const CvBuildingClassInfo& kBuildingClassInfo = buildingEntry->GetBuildingClassInfo();

	int iOldNumBuilding = GetNumRealBuilding(eIndex);
	m_paiNumRealBuilding[eIndex] = iNewValue;

	if (GetNumRealBuilding(eIndex) > 0)
	{
		SetBuildingOriginalOwner(eIndex, eOriginalOwner);
		SetBuildingOriginalTime(eIndex, iOriginalTime);
	}
	else
	{
		SetBuildingOriginalOwner(eIndex, NO_PLAYER);
		SetBuildingOriginalTime(eIndex, MIN_INT);
	}

	// Process building effects
	m_pCity->processBuilding(eIndex, iChangeNumRealBuilding, bFirst);

	// Maintenance cost
	if (buildingEntry->GetGoldMaintenance() != 0)
	{
		pPlayer->GetTreasury()->ChangeBaseBuildingGoldMaintenance(buildingEntry->GetGoldMaintenance() * iChangeNumRealBuilding);
	}

#if !defined(NO_ACHIEVEMENTS)
	// Achievement for Temples
	const char *szBuildingTypeC = buildingEntry->GetType();
	CvString szBuildingType = szBuildingTypeC;
	if (szBuildingType == "BUILDING_TEMPLE")
	{
		if (m_pCity->getOwner() == GC.getGame().getActivePlayer())
		{
			gDLL->IncrementSteamStatAndUnlock(ESTEAMSTAT_TEMPLES, 1000, ACHIEVEMENT_1000TEMPLES);
		}
	}
#endif

	if (buildingEntry->GetPreferredDisplayPosition() > 0)
	{
		auto_ptr<ICvCity1> pDllCity(new CvDllCity(m_pCity));

		if (iNewValue > 0)
		{
			// if this is a WW that (likely has a half-built state)
			if (isWorldWonderClass(kBuildingClassInfo))
			{
				if (GetBuildingProduction(eIndex))
				{
					GC.GetEngineUserInterface()->AddDeferredWonderCommand(WONDER_EDITED, pDllCity.get(), eIndex, 1);
				}
				else
				{
					GC.GetEngineUserInterface()->AddDeferredWonderCommand(WONDER_CREATED, pDllCity.get(), eIndex, 1);
				}
			}
			else
			{
				GC.GetEngineUserInterface()->AddDeferredWonderCommand(WONDER_CREATED, pDllCity.get(), eIndex, 1);
			}
		}
		else
		{
			GC.GetEngineUserInterface()->AddDeferredWonderCommand(WONDER_REMOVED, pDllCity.get(), eIndex, 0);
		}
	}

	if (!(kBuildingClassInfo.isNoLimit()))
	{
		if (isWorldWonderClass(kBuildingClassInfo))
		{
			m_pCity->changeNumWorldWonders(iChangeNumRealBuilding);
			pPlayer->ChangeNumWonders(iChangeNumRealBuilding);
		}
		else if (isTeamWonderClass(kBuildingClassInfo))
		{
			m_pCity->changeNumTeamWonders(iChangeNumRealBuilding);
		}
		else if (isNationalWonderClass(kBuildingClassInfo))
		{
			m_pCity->changeNumNationalWonders(iChangeNumRealBuilding);
			if (m_pCity->isHuman() && !GC.getGame().isGameMultiPlayer())
			{
				IncrementWonderStats(buildingClassType);
			}
		}
		else
		{
			ChangeNumBuildings(iChangeNumRealBuilding);
		}
	}

	if (buildingEntry->IsCityWall())
	{
		auto_ptr<ICvPlot1> pDllPlot(new CvDllPlot(m_pCity->plot()));
		gDLL->GameplayWallCreated(pDllPlot.get());
	}

	// Update the amount of a Resource used up by this Building
	int iNumResources = GC.getNumResourceInfos();
	for (int iResourceLoop = 0; iResourceLoop < iNumResources; iResourceLoop++)
	{
		if (buildingEntry->GetResourceQuantityRequirement(iResourceLoop) > 0)
		{
			pPlayer->changeNumResourceUsed((ResourceTypes)iResourceLoop, iChangeNumRealBuilding * buildingEntry->GetResourceQuantityRequirement(iResourceLoop));
		}
	}

	if (iChangeNumRealBuilding > 0)
	{
		if (bFirst)
		{
			if (GC.getGame().isFinalInitialized() /* && !(gDLL->GetWorldBuilderMode() )*/)
			{
				// World Wonder Notification
				if (isWorldWonderClass(kBuildingClassInfo))
				{
					Localization::String localizedText = Localization::Lookup("TXT_KEY_MISC_COMPLETES_WONDER");
					localizedText << pPlayer->getNameKey() << buildingEntry->GetTextKey();
					GC.getGame().addReplayMessage(REPLAY_MESSAGE_MAJOR_EVENT, m_pCity->getOwner(), localizedText.toUTF8(), m_pCity->getX(), m_pCity->getY());

					bool bDontShowRewardPopup = GC.GetEngineUserInterface()->IsOptionNoRewardPopups();

					// Notification in MP games
#if defined(MOD_API_EXTENSIONS)
					if (bDontShowRewardPopup || GC.getGame().isReallyNetworkMultiPlayer())
#else
					if (bDontShowRewardPopup || GC.getGame().isNetworkMultiPlayer()) // KWG: Candidate for !GC.getGame().IsOption(GAMEOPTION_SIMULTANEOUS_TURNS)
#endif
					{
						CvNotifications *pNotifications = GET_PLAYER(m_pCity->getOwner()).GetNotifications();
						if (pNotifications)
						{
							localizedText = Localization::Lookup("TXT_KEY_MISC_WONDER_COMPLETED");
							localizedText << pPlayer->getNameKey() << buildingEntry->GetTextKey();
							pNotifications->Add(NOTIFICATION_WONDER_COMPLETED_ACTIVE_PLAYER, localizedText.toUTF8(), localizedText.toUTF8(), m_pCity->getX(), m_pCity->getY(), eIndex, pPlayer->GetID());
						}
					}
					// Popup in SP games
					else
					{
						if (m_pCity->getOwner() == GC.getGame().getActivePlayer())
						{
							CvPopupInfo kPopup(BUTTONPOPUP_WONDER_COMPLETED_ACTIVE_PLAYER, eIndex);
							GC.GetEngineUserInterface()->AddPopup(kPopup);

#if !defined(NO_ACHIEVEMENTS)
							if (GET_PLAYER(GC.getGame().getActivePlayer()).isHuman())
							{
								gDLL->UnlockAchievement(ACHIEVEMENT_BUILD_WONDER);

								// look to see if all wonders have been built to unlock the other one
								IncrementWonderStats(buildingClassType);
							}
#endif
						}
					}

					// Wonder notification for all other players
					for (int iI = 0; iI < MAX_MAJOR_CIVS; iI++)
					{
						CvPlayerAI &thisPlayer = GET_PLAYER((PlayerTypes)iI);
						if (thisPlayer.isAlive() || thisPlayer.isObserver())
						{
							// Owner already got his messaging
							if (iI != m_pCity->getOwner())
							{
								// If the builder is met, and the city is revealed
								// Special case for DLC_06 Scenario: Always show the more informative notification
								if ((m_pCity->plot()->isRevealed(thisPlayer.getTeam()) && GET_TEAM(thisPlayer.getTeam()).isHasMet(m_pCity->getTeam())) || gDLL->IsModActivated(CIV5_DLC_06_SCENARIO_MODID) || thisPlayer.isObserver())
								{
									CvNotifications *pNotifications = thisPlayer.GetNotifications();
									if (pNotifications)
									{
										localizedText = Localization::Lookup("TXT_KEY_MISC_WONDER_COMPLETED");
										localizedText << pPlayer->getNameKey() << buildingEntry->GetTextKey();
										pNotifications->Add(NOTIFICATION_WONDER_COMPLETED, localizedText.toUTF8(), localizedText.toUTF8(), m_pCity->getX(), m_pCity->getY(), eIndex, pPlayer->GetID());
									}
								}
								else
								{
									CvNotifications *pNotifications = thisPlayer.GetNotifications();
									if (pNotifications)
									{
										localizedText = Localization::Lookup("TXT_KEY_MISC_WONDER_COMPLETED_UNKNOWN");
										localizedText << buildingEntry->GetTextKey();
										pNotifications->Add(NOTIFICATION_WONDER_COMPLETED, localizedText.toUTF8(), localizedText.toUTF8(), -1, -1, eIndex, -1);
									}
								}
							}
						}

#if !defined(NO_ACHIEVEMENTS)
						// Achievements!
						if (pPlayer->GetID() == GC.getGame().getActivePlayer() && strcmp(buildingEntry->GetType(), "BUILDING_GREAT_FIREWALL") == 0)
						{
							gDLL->UnlockAchievement(ACHIEVEMENT_XP1_16);
						}
#endif
					}
				}
			}

			GC.getGame().incrementBuildingClassCreatedCount(buildingClassType);
		}
	}

	m_pCity->updateStrengthValue();

	// Building might affect City Banner stats
	auto_ptr<ICvCity1> pCity = GC.WrapCityPointer(m_pCity);
	GC.GetEngineUserInterface()->SetSpecificCityInfoDirty(pCity.get(), CITY_UPDATE_TYPE_BANNER);

#if !defined(NO_ACHIEVEMENTS)
	// Test for any achievements being unlocked.
	pPlayer->GetPlayerAchievements().FinishedBuilding(m_pCity, eIndex);
#endif
}

/// Accessor: Get number of free buildings of this type in city
int CvCityBuildings::GetNumFreeBuilding(BuildingTypes eIndex) const
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");
	return m_paiNumFreeBuilding[eIndex];
}

/// Accessor: Set number of free buildings of this type in city
void CvCityBuildings::SetNumFreeBuilding(BuildingTypes eIndex, int iNewValue)
{
	CvAssertMsg(eIndex >= 0, "eIndex expected to be >= 0");
	CvAssertMsg(eIndex < m_pBuildings->GetNumBuildings(), "eIndex expected to be < m_pBuildings->GetNumBuildings()");

	if(GetNumFreeBuilding(eIndex) != iNewValue)
	{
		// This condensed logic comes from SetNumRealBuilding()
		int iChangeNumFreeBuilding = iNewValue - GetNumFreeBuilding(eIndex);
		
		m_paiNumFreeBuilding[eIndex] = iNewValue;

		// Process building effects
		m_pCity->processBuilding(eIndex, iChangeNumFreeBuilding, true);

		CvBuildingEntry* buildingEntry = GC.getBuildingInfo(eIndex);
		if(buildingEntry->IsCityWall())
		{
			auto_ptr<ICvPlot1> pDllPlot(new CvDllPlot(m_pCity->plot()));
			gDLL->GameplayWallCreated(pDllPlot.get());
		}

		m_pCity->updateStrengthValue();

		// Building might affect City Banner stats
		auto_ptr<ICvCity1> pCity = GC.WrapCityPointer(m_pCity);
		GC.GetEngineUserInterface()->SetSpecificCityInfoDirty(pCity.get(), CITY_UPDATE_TYPE_BANNER);
	}
}
/// Accessor: Get yield boost for a specific building by yield type
int CvCityBuildings::GetBuildingYieldChange(BuildingClassTypes eBuildingClass, YieldTypes eYield) const
{
	for(std::vector<BuildingYieldChange>::const_iterator it = m_aBuildingYieldChange.begin(); it != m_aBuildingYieldChange.end(); ++it)
	{
		if((*it).eBuildingClass == eBuildingClass && (*it).eYield == eYield)
		{
			return (*it).iChange;
		}
	}

	return 0;
}

/// Accessor: Set yield boost for a specific building by yield type
void CvCityBuildings::SetBuildingYieldChange(BuildingClassTypes eBuildingClass, YieldTypes eYield, int iChange)
{
	for(std::vector<BuildingYieldChange>::iterator it = m_aBuildingYieldChange.begin(); it != m_aBuildingYieldChange.end(); ++it)
	{
		if((*it).eBuildingClass == eBuildingClass && (*it).eYield == eYield)
		{
			int iOldChange = (*it).iChange;
			if(iOldChange != iChange)
			{

				if(iChange == 0)
				{
					m_aBuildingYieldChange.erase(it);
				}
				else
				{
					(*it).iChange = iChange;
				}

				BuildingTypes eBuilding = (BuildingTypes)GC.getCivilizationInfo(m_pCity->getCivilizationType())->getCivilizationBuildings(eBuildingClass);
				if(NO_BUILDING != eBuilding)
				{
					if(GetNumActiveBuilding(eBuilding) > 0)
					{
						m_pCity->ChangeBaseYieldRateFromBuildings(eYield, (iChange - iOldChange) * GetNumActiveBuilding(eBuilding));
					}
				}
			}

			return;
		}
	}

	if(0 != iChange)
	{
		BuildingYieldChange kChange;
		kChange.eBuildingClass = eBuildingClass;
		kChange.eYield = eYield;
		kChange.iChange = iChange;
		m_aBuildingYieldChange.push_back(kChange);

		BuildingTypes eBuilding = (BuildingTypes)m_pCity->getCivilizationInfo().getCivilizationBuildings(eBuildingClass);
		if(NO_BUILDING != eBuilding)
		{
			if(GetNumActiveBuilding(eBuilding) > 0)
			{
				m_pCity->ChangeBaseYieldRateFromBuildings(eYield, iChange * GetNumActiveBuilding(eBuilding));
			}
		}
	}
}

/// Accessor: Change yield boost for a specific building by yield type
void CvCityBuildings::ChangeBuildingYieldChange(BuildingClassTypes eBuildingClass, YieldTypes eYield, int iChange)
{
	SetBuildingYieldChange(eBuildingClass, eYield, GetBuildingYieldChange(eBuildingClass, eYield) + iChange);
}

/// Accessor: Get Great Work in a specific building by slot index
int CvCityBuildings::GetBuildingGreatWork(BuildingClassTypes eBuildingClass, int iSlot) const
{
	for(std::vector<BuildingGreatWork>::const_iterator it = m_aBuildingGreatWork.begin(); it != m_aBuildingGreatWork.end(); ++it)
	{
		if((*it).eBuildingClass == eBuildingClass && (*it).iSlot == iSlot)
		{
			return (*it).iGreatWorkIndex;
		}
	}

	return -1;
}

/// Accessor: Set yield boost for a specific building by yield type
void CvCityBuildings::SetBuildingGreatWork(BuildingClassTypes eBuildingClass, int iSlot, int iGreatWorkIndex)
{
	for(std::vector<BuildingGreatWork>::iterator it = m_aBuildingGreatWork.begin(); it != m_aBuildingGreatWork.end(); ++it)
	{
		if((*it).eBuildingClass == eBuildingClass && (*it).iSlot == iSlot)
		{
			int iOldGreatWorkIndex = (*it).iGreatWorkIndex;
			if (iOldGreatWorkIndex != iGreatWorkIndex)
			{
				if (iGreatWorkIndex == -1)
				{
					m_aBuildingGreatWork.erase(it);
				}
				else
				{
					(*it).iGreatWorkIndex = iGreatWorkIndex;
				}
			}

			GC.GetEngineUserInterface()->setDirty(CityInfo_DIRTY_BIT, true);
			return;
		}
	}

	if (iGreatWorkIndex != -1)
	{
		BuildingGreatWork kWork;
		kWork.eBuildingClass = eBuildingClass;
		kWork.iSlot = iSlot;
		kWork.iGreatWorkIndex = iGreatWorkIndex;
		m_aBuildingGreatWork.push_back(kWork);
	}

	GC.GetEngineUserInterface()->setDirty(CityInfo_DIRTY_BIT, true);
}

/// Accessor: Is there a Great Work inside this building?
bool CvCityBuildings::IsHoldingGreatWork(BuildingClassTypes eBuildingClass) const
{
	for(std::vector<BuildingGreatWork>::const_iterator it = m_aBuildingGreatWork.begin(); it != m_aBuildingGreatWork.end(); ++it)
	{
		if((*it).eBuildingClass == eBuildingClass)
		{
			return true;
		}
	}
	return false;
}

/// Accessor: How many Great Works are inside this building?
int CvCityBuildings::GetNumGreatWorksInBuilding(BuildingClassTypes eBuildingClass) const
{
	int iCount = 0;
	for(std::vector<BuildingGreatWork>::const_iterator it = m_aBuildingGreatWork.begin(); it != m_aBuildingGreatWork.end(); ++it)
	{
		if((*it).eBuildingClass == eBuildingClass)
		{
			iCount++;
		}
	}
	return iCount;
}

/// Accessor: Is there a Great Work slot somewhere in the city?
bool CvCityBuildings::HasAnyAvailableGreatWorkSlot() const
{
	BuildingClassTypes eBuildingClass = NO_BUILDINGCLASS; // Passed by reference below
	int iSlot = -1; // Passed by reference below

	return GetNextAvailableGreatWorkSlot (&eBuildingClass, &iSlot);
}

/// Accessor: Is there a Great Work slot of this type somewhere in the city?
bool CvCityBuildings::HasAvailableGreatWorkSlot(GreatWorkSlotType eSlotType) const
{
	BuildingClassTypes eBuildingClass = NO_BUILDINGCLASS; // Passed by reference below
	int iSlot = -1; // Passed by reference below

	return GetNextAvailableGreatWorkSlot (eSlotType, &eBuildingClass, &iSlot);
}

/// Accessor: How many Great Work slots of this type are in the city?
int CvCityBuildings::GetNumAvailableGreatWorkSlots() const
{
	int iCount = 0;
	CvPlayerAI &kPlayer = GET_PLAYER(m_pCity->getOwner());

	for(int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
	{
		BuildingClassTypes eLoopBuildingClass = (BuildingClassTypes) iI;
		if(m_pCity->GetNumBuildingClass(eLoopBuildingClass) > 0)
		{
			BuildingTypes eBuilding = kPlayer.GetCivBuilding(eLoopBuildingClass);
			if(NO_BUILDING != eBuilding)
			{
				if (GetNumBuilding(eBuilding) > 0)
				{
					CvBuildingEntry *pkBuilding = GC.getBuildingInfo(eBuilding);
					if (pkBuilding)
					{
						int iNumSlots = pkBuilding->GetGreatWorkCount();
						int iNumOpenSlots = iNumSlots - GetNumGreatWorksInBuilding(eLoopBuildingClass);
						if(iNumOpenSlots > 0)
						{
							iCount += iNumOpenSlots;
						}
					}
				}
			}
		}
	}

	return iCount;
}

/// Accessor: How many Great Work slots of this type are in the city?
int CvCityBuildings::GetNumAvailableGreatWorkSlots(GreatWorkSlotType eSlotType) const
{
	int iCount = 0;
	CvPlayerAI &kPlayer = GET_PLAYER(m_pCity->getOwner());

	for(int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
	{
		BuildingClassTypes eLoopBuildingClass = (BuildingClassTypes) iI;
		if(m_pCity->GetNumBuildingClass(eLoopBuildingClass) > 0)
		{
			BuildingTypes eBuilding = kPlayer.GetCivBuilding(eLoopBuildingClass);
			if(NO_BUILDING != eBuilding)
			{
				if (GetNumBuilding(eBuilding) > 0)
				{
					CvBuildingEntry *pkBuilding = GC.getBuildingInfo(eBuilding);
					if (pkBuilding)
					{
						if (pkBuilding->GetGreatWorkSlotType() == eSlotType)
						{
							int iNumSlots = pkBuilding->GetGreatWorkCount();
							int iNumOpenSlots = iNumSlots - GetNumGreatWorksInBuilding(eLoopBuildingClass);
							if(iNumOpenSlots > 0)
							{
								iCount += iNumOpenSlots;
							}
						}
					}
				}
			}
		}
	}

	return iCount;
}

/// Accessor: Is there a Great Work slot of this type somewhere in the city?
bool CvCityBuildings::GetNextAvailableGreatWorkSlot(BuildingClassTypes *eBuildingClass, int *iSlot) const
{
	if (eBuildingClass && iSlot)
	{
		CvPlayerAI &kPlayer = GET_PLAYER(m_pCity->getOwner());
		for(int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
		{
			BuildingClassTypes eLoopBuildingClass = (BuildingClassTypes) iI;
			if(m_pCity->GetNumBuildingClass(eLoopBuildingClass) <= 0) continue;
			BuildingTypes eBuilding = kPlayer.GetCivBuilding(eLoopBuildingClass);
			if(NO_BUILDING != eBuilding)
			{
				if (GetNumBuilding(eBuilding) > 0)
				{
					int iNumSlots = GC.getBuildingInfo(eBuilding)->GetGreatWorkCount();
					for (int jJ = 0; jJ < iNumSlots; jJ++)
					{
						if (GetBuildingGreatWork (eLoopBuildingClass, jJ) == NO_GREAT_WORK)
						{
							*eBuildingClass = eLoopBuildingClass;
							*iSlot = jJ;
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

/// Accessor: Is there a Great Work slot of this type somewhere in the city?
bool CvCityBuildings::GetNextAvailableGreatWorkSlot(GreatWorkSlotType eGreatWorkSlot, BuildingClassTypes *eBuildingClass, int *iSlot) const
{
	if (eBuildingClass && iSlot)
	{
		CvPlayerAI &kPlayer = GET_PLAYER(m_pCity->getOwner());
		for(int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
		{
			BuildingClassTypes eLoopBuildingClass = (BuildingClassTypes) iI;
			if(m_pCity->GetNumBuildingClass(eLoopBuildingClass) <= 0) continue;
			BuildingTypes eBuilding = kPlayer.GetCivBuilding(eLoopBuildingClass);
			if(NO_BUILDING != eBuilding)
			{
				if (GetNumBuilding(eBuilding) > 0)
				{
					if (GC.getBuildingInfo(eBuilding)->GetGreatWorkSlotType() == eGreatWorkSlot)
					{
						int iNumSlots = GC.getBuildingInfo(eBuilding)->GetGreatWorkCount();
						for (int jJ = 0; jJ < iNumSlots; jJ++)
						{
							if (GetBuildingGreatWork (eLoopBuildingClass, jJ) == NO_GREAT_WORK)
							{
								*eBuildingClass = eLoopBuildingClass;
								*iSlot = jJ;
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}

#if defined(MOD_GLOBAL_GREATWORK_YIELDTYPES) || defined(MOD_API_UNIFIED_YIELDS)
/// Accessor: How much of this yield are we generating from Great Works in our buildings?
int CvCityBuildings::GetYieldFromGreatWorks(YieldTypes eYield) const
{
	CvPlayerAI &kPlayer = GET_PLAYER(m_pCity->getOwner());
	int iYieldPerBuilding = GC.getBASE_CULTURE_PER_GREAT_WORK();
	int iYieldPerWork = kPlayer.GetGreatWorkYieldChange(eYield);
	iYieldPerWork += kPlayer.GetPlayerTraits()->GetGreatWorkYieldChanges(eYield);

	ReligionTypes eMajority = m_pCity->GetCityReligions()->GetReligiousMajority();
	if(eMajority >= RELIGION_PANTHEON)
	{
		const CvReligion* pReligion = GC.getGame().GetGameReligions()->GetReligion(eMajority, m_pCity->getOwner());
		if(pReligion)
		{
			iYieldPerWork += pReligion->m_Beliefs.GetGreatWorkYieldChange(m_pCity->getPopulation(), eYield);
			BeliefTypes eSecondaryPantheon = m_pCity->GetCityReligions()->GetSecondaryReligionPantheonBelief();
			if (eSecondaryPantheon != NO_BELIEF)
			{
				iYieldPerWork += GC.GetGameBeliefs()->GetEntry(eSecondaryPantheon)->GetGreatWorkYieldChange(eYield);
			}
		}
	}

	int iWorkCount = 0;
	int iBuildingCount = 0;

	for(std::vector<BuildingGreatWork>::const_iterator it = m_aBuildingGreatWork.begin(); it != m_aBuildingGreatWork.end(); ++it)
	{
		BuildingClassTypes eBldgClass = (*it).eBuildingClass;
		CvBuildingClassInfo *pkClassInfo = GC.getBuildingClassInfo(eBldgClass);
		if (pkClassInfo)
		{
			BuildingTypes eBuilding = kPlayer.GetCivBuilding(eBldgClass);
			CvBuildingEntry *pkInfo = GC.getBuildingInfo(eBuilding);
			if (pkInfo)
			{
				iWorkCount++;
				
				if ((MOD_GLOBAL_GREATWORK_YIELDTYPES && eYield == pkInfo->GetGreatWorkYieldType()) || (!MOD_GLOBAL_GREATWORK_YIELDTYPES && eYield == YIELD_CULTURE))
				{
					iBuildingCount++;
				}
			}
		}
	}
	int iRtnValue = (iWorkCount * iYieldPerWork) + (iBuildingCount * iYieldPerBuilding);
#if defined(MOD_GLOBAL_GREATWORK_YIELDTYPES)
	iRtnValue += GetThemingBonuses(eYield);
#else
	if (eYield == YIELD_CULTURE) {
		iRtnValue += GetThemingBonuses();
	}
#endif

	return iRtnValue;
}
#endif

/// Accessor: How much culture are we generating from Great Works in our buildings?
int CvCityBuildings::GetCultureFromGreatWorks() const
{
#if defined(MOD_GLOBAL_GREATWORK_YIELDTYPES) || defined(MOD_API_UNIFIED_YIELDS)
	return GetYieldFromGreatWorks(YIELD_CULTURE);
#else
	int iCulturePerWork = GC.getBASE_CULTURE_PER_GREAT_WORK();
	iCulturePerWork += GET_PLAYER(m_pCity->getOwner()).GetGreatWorkYieldChange(YIELD_CULTURE);

	int iRtnValue = iCulturePerWork * m_aBuildingGreatWork.size();
	iRtnValue += GetThemingBonuses();

	return iRtnValue;
#endif
}

/// Accessor: How many Great Works of specific slot type present in this city?
#if defined(MOD_GLOBAL_GREATWORK_YIELDTYPES)
#endif
int CvCityBuildings::GetNumGreatWorks(bool bIgnoreYield, bool bIncludeArtifact, bool bIncludeGreatWork) const
{
#if defined(MOD_GLOBAL_GREATWORK_YIELDTYPES)
	int iRtnValue = 0;

	GreatWorkClass eArtifactClass = (GreatWorkClass)GC.getInfoTypeForString("GREAT_WORK_ARTIFACT");
	GreatWorkClass eArtClass = (GreatWorkClass)GC.getInfoTypeForString("GREAT_WORK_ART");
	CvPlayerAI &kPlayer = GET_PLAYER(m_pCity->getOwner());
	for(std::vector<BuildingGreatWork>::const_iterator it = m_aBuildingGreatWork.begin(); it != m_aBuildingGreatWork.end(); ++it)
	{
		BuildingClassTypes eBldgClass = (*it).eBuildingClass;
		CvBuildingClassInfo *pkClassInfo = GC.getBuildingClassInfo(eBldgClass);
		if(!pkClassInfo) continue;
		
		BuildingTypes eBuilding = kPlayer.GetCivBuilding(eBldgClass);
		CvBuildingEntry *pkInfo = GC.getBuildingInfo(eBuilding);
		if(!pkInfo) continue;
		
		if(!bIgnoreYield && pkInfo->GetGreatWorkYieldType() == NO_YIELD) continue;
		if(!bIncludeArtifact && GC.getGame().GetGameCulture()->GetGreatWorkClass((*it).iGreatWorkIndex) == eArtifactClass) continue;
		if(!bIncludeGreatWork && GC.getGame().GetGameCulture()->GetGreatWorkClass((*it).iGreatWorkIndex) == eArtClass) continue;

		iRtnValue++;
	}
	return iRtnValue;
#else
	// Simple if want total of all types
	return m_aBuildingGreatWork.size();
#endif
}

/// Accessor: How many Great Works of specific slot type present in this city?
int CvCityBuildings::GetNumGreatWorks(GreatWorkSlotType eGreatWorkSlot) const
{
	int iRtnValue = 0;
	CvPlayerAI &kPlayer = GET_PLAYER(m_pCity->getOwner());

	for(std::vector<BuildingGreatWork>::const_iterator it = m_aBuildingGreatWork.begin(); it != m_aBuildingGreatWork.end(); ++it)
	{
		BuildingClassTypes eBldgClass = (*it).eBuildingClass;
		CvBuildingClassInfo *pkClassInfo = GC.getBuildingClassInfo(eBldgClass);
		if (pkClassInfo)
		{
			BuildingTypes eBuilding = kPlayer.GetCivBuilding(eBldgClass);;
			CvBuildingEntry *pkInfo = GC.getBuildingInfo(eBuilding);
			if (pkInfo)
			{
				if (pkInfo->GetGreatWorkSlotType() == eGreatWorkSlot)
				{
					iRtnValue++;
				}
			}
		}
	}

	return iRtnValue;
}

/// Accessor: Get tourism converted from culture from Improvements and Wonders
int CvCityBuildings::GetLandmarksTourismPercent() const
{
	return m_iLandmarksTourismPercent;
}

/// Accessor: Change tourism converted from culture from Improvements and Wonders
void CvCityBuildings::ChangeLandmarksTourismPercent(int iChange)
{
	if(iChange != 0)
	{
		m_iLandmarksTourismPercent = (m_iLandmarksTourismPercent + iChange);
		CvAssert(m_iLandmarksTourismPercent >= 0);
	}
}

/// Accessor: Get extra times to spread religion for missionaries from this city
int CvCityBuildings::GetGreatWorksTourismModifier() const
{
	return m_iGreatWorksTourismModifier;
}

/// Accessor: Change extra times to spread religion for missionaries from this city
void CvCityBuildings::ChangeGreatWorksTourismModifier(int iChange)
{
	if(iChange != 0)
	{
		m_iGreatWorksTourismModifier = (m_iGreatWorksTourismModifier + iChange);
	}
}

/// Accessor: How many buildings in this city are ones that are built through Faith?
int CvCityBuildings::GetNumBuildingsFromFaith() const
{
	return m_iNumBuildingsFromFaith;
}
void CvCityBuildings::ChangeNumBuildingsFromFaith(int iChange)
{
	if(iChange != 0)
	{
		m_iNumBuildingsFromFaith = (m_iNumBuildingsFromFaith + iChange);
	}
}

/// Accessor: Total theming bonus from all buildings in the city
#if defined(MOD_GLOBAL_GREATWORK_YIELDTYPES)
int CvCityBuildings::GetThemingBonuses(YieldTypes eYield) const
#else
int CvCityBuildings::GetThemingBonuses() const
#endif
{
	int iBonus = 0;
	CvPlayerAI &kPlayer = GET_PLAYER(m_pCity->getOwner());

	for(int iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
	{
		BuildingClassTypes eLoopBuildingClass = (BuildingClassTypes) iI;
		if(m_pCity->GetNumBuildingClass(eLoopBuildingClass) > 0)
		{
			BuildingTypes eBuilding = kPlayer.GetCivBuilding(eLoopBuildingClass);
			if(NO_BUILDING != eBuilding)
			{
				if (GetNumBuilding(eBuilding) > 0)
				{
#if defined(MOD_GLOBAL_GREATWORK_YIELDTYPES)
					CvBuildingEntry *pkInfo = GC.getBuildingInfo(eBuilding);
					if (pkInfo)
					{
						if (pkInfo->GetGreatWorkYieldType() == eYield)
						{
							iBonus += m_pCity->GetCityCulture()->GetThemingBonus(eLoopBuildingClass);
						}
					}
#else
					iBonus += m_pCity->GetCityCulture()->GetThemingBonus(eLoopBuildingClass);
#endif
				}
			}
		}
	}

	return iBonus;
}

/// Accessor: Get current production modifier from buildings
int CvCityBuildings::GetBuildingProductionModifier() const
{
	return m_iBuildingProductionModifier;
}

/// Accessor: Change current production modifier from buildings
void CvCityBuildings::ChangeBuildingProductionModifier(int iChange)
{
	m_iBuildingProductionModifier = (m_iBuildingProductionModifier + iChange);
	CvAssert(GetBuildingProductionModifier() >= 0);
}

/// Accessor: Get current defense boost from buildings
int CvCityBuildings::GetBuildingDefense() const
{
	return m_iBuildingDefense;
}

/// Accessor: Change current defense boost from buildings
void CvCityBuildings::ChangeBuildingDefense(int iChange)
{
	if(iChange != 0)
	{
		m_iBuildingDefense = (m_iBuildingDefense + iChange);
		CvAssert(GetBuildingDefense() >= 0);

		m_pCity->plot()->plotAction(PUF_makeInfoBarDirty);
	}
}

/// Accessor: Get current defense boost Mod from buildings
int CvCityBuildings::GetBuildingDefenseMod() const
{
	return m_iBuildingDefenseMod;
}

/// Accessor: Change current defense boost mod from buildings
void CvCityBuildings::ChangeBuildingDefenseMod(int iChange)
{
	if(iChange != 0)
	{
		m_iBuildingDefenseMod = (m_iBuildingDefenseMod + iChange);
		CvAssert(m_iBuildingDefenseMod >= 0);

		m_pCity->plot()->plotAction(PUF_makeInfoBarDirty);
	}
}

/// Accessor: Get extra times to spread religion for missionaries from this city
int CvCityBuildings::GetMissionaryExtraSpreads() const
{
	return m_iMissionaryExtraSpreads;
}

/// Accessor: Change extra times to spread religion for missionaries from this city
void CvCityBuildings::ChangeMissionaryExtraSpreads(int iChange)
{
	if(iChange != 0)
	{
		m_iMissionaryExtraSpreads = (m_iMissionaryExtraSpreads + iChange);
		CvAssert(m_iMissionaryExtraSpreads >= 0);
	}
}

void CvCityBuildings::IncrementWonderStats(BuildingClassTypes eIndex)
{
	CvBuildingClassInfo* pkBuildingClassInfo = GC.getBuildingClassInfo(eIndex);
	if(pkBuildingClassInfo == NULL)
		return;

	const char* szWonderTypeChar = pkBuildingClassInfo->GetType();
	CvString szWonderType = szWonderTypeChar;

	if(szWonderType == "BUILDINGCLASS_HEROIC_EPIC")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_HEROICEPIC);
	}
	else if(szWonderType == "BUILDINGCLASS_NATIONAL_COLLEGE")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_NATIONALCOLLEGE);
	}
	else if(szWonderType == "BUILDINGCLASS_NATIONAL_EPIC")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_NATIONALEPIC);
	}
	else if(szWonderType == "BUILDINGCLASS_IRONWORKS")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_IRONWORKS);
	}
	else if(szWonderType == "BUILDINGCLASS_OXFORD_UNIVERSITY")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_OXFORDUNIVERSITY);
	}
	else if(szWonderType == "BUILDINGCLASS_HERMITAGE")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_HERMITAGE);
	}
	else if(szWonderType == "BUILDINGCLASS_GREAT_LIGHTHOUSE")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_GREATLIGHTHOUSE);
	}
	else if(szWonderType == "BUILDINGCLASS_STONEHENGE")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_STONEHENGE);
	}
	else if(szWonderType == "BUILDINGCLASS_GREAT_LIBRARY")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_GREATLIBRARY);
	}
	else if(szWonderType == "BUILDINGCLASS_PYRAMID")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_PYRAMIDS);
	}
	else if(szWonderType == "BUILDINGCLASS_COLOSSUS")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_COLOSSUS);
	}
	else if(szWonderType == "BUILDINGCLASS_ORACLE")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_ORACLE);
	}
	else if(szWonderType == "BUILDINGCLASS_HANGING_GARDEN")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_HANGINGGARDENS);
	}
	else if(szWonderType == "BUILDINGCLASS_GREAT_WALL")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_GREATWALL);
	}
	else if(szWonderType == "BUILDINGCLASS_ANGKOR_WAT")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_ANGKORWAT);
	}
	else if(szWonderType == "BUILDINGCLASS_HAGIA_SOPHIA")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_HAGIASOPHIA);
	}
	else if(szWonderType == "BUILDINGCLASS_CHICHEN_ITZA")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_CHICHENITZA);
	}
	else if(szWonderType == "BUILDINGCLASS_MACHU_PICHU")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_MACHUPICCHU);
	}
	else if(szWonderType == "BUILDINGCLASS_NOTRE_DAME")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_NOTREDAME);
	}
	else if(szWonderType == "BUILDINGCLASS_PORCELAIN_TOWER")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_PORCELAINTOWER);
	}
	else if(szWonderType == "BUILDINGCLASS_HIMEJI_CASTLE")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_HIMEJICASTLE);
	}
	else if(szWonderType == "BUILDINGCLASS_SISTINE_CHAPEL")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_SISTINECHAPEL);
	}
	else if(szWonderType == "BUILDINGCLASS_KREMLIN")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_KREMLIN);
	}
	else if(szWonderType == "BUILDINGCLASS_FORBIDDEN_PALACE")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_FORBIDDENPALACE);
	}
	else if(szWonderType == "BUILDINGCLASS_TAJ_MAHAL")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_TAJMAHAL);
	}
	else if(szWonderType == "BUILDINGCLASS_BIG_BEN")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_BIGBEN);
	}
	else if(szWonderType == "BUILDINGCLASS_LOUVRE")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_LOUVRE);
	}
	else if(szWonderType == "BUILDINGCLASS_BRANDENBURG_GATE")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_BRANDENBURGGATE);
	}
	else if(szWonderType == "BUILDINGCLASS_STATUE_OF_LIBERTY")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_STATUEOFLIBERTY);
	}
	else if(szWonderType == "BUILDINGCLASS_CRISTO_REDENTOR")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_CRISTOREDENTOR);
	}
	else if(szWonderType == "BUILDINGCLASS_EIFFEL_TOWER")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_EIFFELTOWER);
	}
	else if(szWonderType == "BUILDINGCLASS_PENTAGON")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_PENTAGON);
	}
	else if(szWonderType == "BUILDINGCLASS_UNITED_NATIONS")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_UNITEDNATION);
	}
	else if(szWonderType == "BUILDINGCLASS_SYDNEY_OPERA_HOUSE")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_SYDNEYOPERAHOUSE);
	}
	else if(szWonderType == "BUILDINGCLASS_STATUE_ZEUS")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_STATUEOFZEUS);
	}
	else if(szWonderType == "BUILDINGCLASS_TEMPLE_ARTEMIS")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_TEMPLEOFARTEMIS);
	}
	else if(szWonderType == "BUILDINGCLASS_MAUSOLEUM_HALICARNASSUS")
	{
		gDLL->IncrementSteamStat(ESTEAMSTAT_MAUSOLEUMOFHALICARNASSUS);
	}
	else
	{
		OutputDebugString("\nNo Stat for selected Wonder: ");
		OutputDebugString(szWonderType);
		OutputDebugString("\n");
	}

#if !defined(NO_ACHIEVEMENTS)
	bool bCheckForWonders = false;
	bCheckForWonders = CheckForAllWondersBuilt();
	if(bCheckForWonders)
	{
		gDLL->UnlockAchievement(ACHIEVEMENT_ALL_WONDERS);
	}
#endif

#if !defined(NO_ACHIEVEMENTS)
	//DLC_06
	bool bCheckForAncientWonders = false;
	bCheckForAncientWonders = CheckForSevenAncientWondersBuilt();
	if(bCheckForAncientWonders)
	{
		gDLL->UnlockAchievement(ACHIEVEMENT_SPECIAL_ANCIENT_WONDERS);
	}
#endif

}
bool CvCityBuildings::CheckForAllWondersBuilt()
{
	int iI;
	int iStartStatWonder = ESTEAMSTAT_ANGKORWAT;
	int iEndStatWonder = ESTEAMSTAT_PYRAMIDS;		//Don't include the united nations because it was removed in BNW.
	int32 nStat;

	for(iI = iStartStatWonder; iI < iEndStatWonder; iI++)
	{
		if(gDLL->GetSteamStat((ESteamStat)iI, &nStat))
		{
			if(nStat <= 0)
			{
				return false;
			}
		}
	}
	return true;
}

bool CvCityBuildings::CheckForSevenAncientWondersBuilt()
{
	GUID guid;
	ExtractGUID(CIV5_DLC_06_PACKAGEID, guid);

	if(gDLL->IsDLCValid(guid))
	{
		ESteamStat arrWonderStats[7] =
		{
			ESTEAMSTAT_COLOSSUS,
			ESTEAMSTAT_GREATLIGHTHOUSE,
			ESTEAMSTAT_HANGINGGARDENS,
			ESTEAMSTAT_PYRAMIDS,
			ESTEAMSTAT_STATUEOFZEUS,
			ESTEAMSTAT_TEMPLEOFARTEMIS,
			ESTEAMSTAT_MAUSOLEUMOFHALICARNASSUS
		};
		int32 nStat;
		for(int iI = 0; iI < 7; iI++)
		{
			if(gDLL->GetSteamStat(arrWonderStats[iI], &nStat))
			{
				if(nStat <= 0)
				{
					return false;
				}
			}
			else
			{
				// Couldn't get one of the SteamStats for some reason
				return false;
			}
		}
		return true;
	}
	return false;
}

/// Uses the notification system to send information out when other players need to know a building has been started
void CvCityBuildings::NotifyNewBuildingStarted(BuildingTypes /*eIndex*/)
{
	// JON: Disabling this notification
	return;

	// is this city starting a wonder? If so, send a notification
	//CvBuildingEntry* buildingEntry = GC.getBuildingInfo(eIndex);
	//if (isLimitedWonderClass((BuildingClassTypes)(buildingEntry->GetBuildingClassType())) && GetBuildingProductionTimes100(eIndex) == 0)
	//{
	//	Localization::String locString;
	//	Localization::String locSummaryString;

	//	for (uint ui = 0; ui < MAX_MAJOR_CIVS; ui++)
	//	{
	//		PlayerTypes ePlayer = (PlayerTypes)ui;

	//		if (ePlayer == m_pCity->getOwner() || !GET_PLAYER(ePlayer).isAlive())
	//		{
	//			continue;
	//		}

	//		int iX = -1;
	//		int iY = -1;
	//		int iPlayerID = -1;

	//		if (GET_TEAM(m_pCity->getTeam()).isHasMet(GET_PLAYER(ePlayer).getTeam()))
	//		{
	//			if (m_pCity->isRevealed(GET_PLAYER(ePlayer).getTeam(), false))
	//			{
	//				locString = Localization::Lookup("TXT_KEY_NOTIFICATION_WONDER_STARTED");
	//				locString << GET_PLAYER(m_pCity->getOwner()).getNameKey() << buildingEntry->GetTextKey() << m_pCity->getNameKey();
	//			}
	//			else
	//			{
	//				locString = Localization::Lookup("TXT_KEY_NOTIFICATION_WONDER_STARTED_UNKNOWN_LOCATION");
	//				locString << GET_PLAYER(m_pCity->getOwner()).getNameKey() << buildingEntry->GetTextKey();
	//			}


	//			locSummaryString = Localization::Lookup("TXT_KEY_NOTIFICATION_SUMMARY_WONDER_STARTED");
	//			locSummaryString << GET_PLAYER(m_pCity->getOwner()).getNameKey() << buildingEntry->GetTextKey();

	//		}
	//		else
	//		{
	//			locString = Localization::Lookup("TXT_KEY_NOTIFICATION_WONDER_STARTED_UNMET");
	//			locString << buildingEntry->GetTextKey();
	//			locSummaryString = Localization::Lookup("TXT_KEY_NOTIFICATION_SUMMARY_WONDER_STARTED_UNKNOWN");
	//			locSummaryString << buildingEntry->GetTextKey();
	//		}

	//		CvNotifications* pNotifications = GET_PLAYER(ePlayer).GetNotifications();
	//		if (pNotifications)
	//		{
	//			pNotifications->Add(NOTIFICATION_WONDER_STARTED, locString.toUTF8(), locSummaryString.toUTF8(), iX, iY, eIndex);
	//		}
	//	}
	//}
}

/// Helper function to read in an integer array of data sized according to number of building types
void BuildingArrayHelpers::Read(FDataStream& kStream, int* paiBuildingArray)
{
	int iNumEntries;
	int iType;

	kStream >> iNumEntries;

	for(int iI = 0; iI < iNumEntries; iI++)
	{
		bool bValid = true;
		iType = CvInfosSerializationHelper::ReadHashed(kStream, &bValid);
		if(iType != -1 || !bValid)
		{
			if(iType != -1)
			{
				kStream >> paiBuildingArray[iType];
			}
			else
			{
				CvString szError;
				szError.Format("LOAD ERROR: Building Type not found");
				GC.LogMessage(szError.GetCString());
				CvAssertMsg(false, szError);
				int iDummy;
				kStream >> iDummy; // Skip it.
			}
		}
	}
}

/// Helper function to write out an integer array of data sized according to number of building types
void BuildingArrayHelpers::Write(FDataStream& kStream, int* paiBuildingArray, int iArraySize)
{
	kStream << iArraySize;

	for(int iI = 0; iI < iArraySize; iI++)
	{
		const BuildingTypes eBuilding = static_cast<BuildingTypes>(iI);
		CvBuildingEntry* pkBuildingInfo = GC.getBuildingInfo(eBuilding);
		if(pkBuildingInfo)
		{
			CvInfosSerializationHelper::WriteHashed(kStream, pkBuildingInfo);;
			kStream << paiBuildingArray[iI];
		}
		else
		{
			kStream << (int)0;
		}
	}
}
