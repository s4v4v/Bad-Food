class ActionFold_FoldingShovelCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(1.0);
	}
};

class ActionFold_FoldingShovel: ActionContinuousBase
{
	void ActionFold_FoldingShovel()
	{

	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "Fold";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( item )
		{ 
			return true;
		}
		return false;
	}

	override void OnEndServer( ActionData action_data )
	{
		action_data.m_MainItem.SetAnimationPhase("Fold", 1.0);
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(Swapper, 1000, false, action_data);
	}

	void Swapper ( ActionData action_data )
	{
		FoldShovelLambda lambda = new FoldShovelLambda(action_data.m_MainItem, "Spur_FoldingShovel_Folded", action_data.m_Player);
        lambda.SetTransferParams(true, true, true);
        action_data.m_Player.ServerReplaceItemInHandsWithNew(lambda);
	}
	
};

class FoldShovelLambda : TurnItemIntoItemLambda
{
	void FoldShovelLambda (EntityAI old_item, string new_item_type, PlayerBase player)
	{
	}
};
