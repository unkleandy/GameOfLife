#include "EcaActionKeyBinding.h"


#include "Model.h"
#include "Controller.h"




EcaActionKeyBinding::EcaActionKeyBinding()
	: EcaActionKeyBinding(std::numeric_limits<char>::min(), std::numeric_limits<char>::max())
{
}

EcaActionKeyBinding::EcaActionKeyBinding(key_t bindFromKey, key_t bindToKey)
	: mOffsetKey{ bindFromKey }, mBinding(bindToKey - bindFromKey + 1)
{
	std::fill(mBinding.begin(), mBinding.end(), nullptr);
}

void EcaActionKeyBinding::setAction(key_t key, action_t action)
{
	mBinding[key - mOffsetKey] = action;
}

void EcaActionKeyBinding::setAction(key_t keyTarget, key_t keySource)
{
	mBinding[keyTarget - mOffsetKey] = mBinding[keySource - mOffsetKey];
}

void EcaActionKeyBinding::setDefaultAction(action_t action)
{
	mDefaultAction = action;
}

void EcaActionKeyBinding::setDefaultAction(key_t key)
{
	mDefaultAction = mBinding[key - mOffsetKey];
}

void EcaActionKeyBinding::doActionFromKey(key_t key, Model & model, Controller & controller, View & view) const
{
	int index{ key - mOffsetKey };
	if (index >= 0 && index < (int)mBinding.size() && mBinding[index]) {
		mBinding[key - mOffsetKey](model, controller, view);
	} else {
		doDefaultAction(model, controller, view);
	}
}

void EcaActionKeyBinding::doDefaultAction(Model & model, Controller & controller, View & view) const
{
	if (mDefaultAction) {
		mDefaultAction(model, controller, view);
	}
}
