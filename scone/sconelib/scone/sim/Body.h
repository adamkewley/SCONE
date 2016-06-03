#pragma once

#include "sim.h"
#include "scone/core/HasName.h"
#include "scone/core/math.h"
#include "scone/core/Vec3.h"
#include "scone/core/Quat.h"

namespace scone
{
	namespace sim
	{
		class SCONE_API Body : public HasName
		{
		public:
			Body();
			virtual ~Body();

			virtual Vec3 GetPos() const = 0;
			virtual Quat GetOri() const = 0;

			virtual Vec3 GetLinVel() const = 0;
			virtual Vec3 GetAngVel() const = 0;

			virtual Vec3 GetContactForce() const = 0;
			virtual Vec3 GetContactTorque() const = 0;

			virtual const Model& GetModel() const = 0;
			virtual Model& GetModel() = 0;
		};
	}
}