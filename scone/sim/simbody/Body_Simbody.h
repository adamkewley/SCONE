#pragma once

#include "sim_simbody.h"
#include "../Body.h"

namespace OpenSim
{
	class Body;
}

namespace scone
{
	namespace sim
	{
		class SCONE_SIM_SIMBODY_API Body_Simbody : public Body
		{
		public:
			Body_Simbody( class Model_Simbody& model, OpenSim::Body& body );
			virtual ~Body_Simbody() { };

			virtual Vec3 GetPos() const override;
			virtual Quat GetOri() const override;

			virtual Vec3 GetLinVel() const override;
			virtual Vec3 GetAngVel() const override;

			virtual const String& GetName() const override;

			virtual Vec3 GetContactForce() const override;
			virtual Vec3 GetContactTorque() const override;

			OpenSim::Body& m_osBody;
			class Model_Simbody& m_Model;

		private:
			int m_ForceIndex;
		};
	}
}
