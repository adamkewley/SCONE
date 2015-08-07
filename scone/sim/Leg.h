#pragma once

#include "Link.h"
#include "Types.h"
#include "../core/Vec3.h"
#include "../core/HasName.h"
#include "Body.h"
#include "Area.h"

namespace scone
{
	namespace sim
	{
		class SCONE_SIM_API Leg : public HasName
		{
		public:
			Leg( Link& upper, Link& foot, size_t index, Side side = NoSide, size_t rank = 0 );
			virtual ~Leg();

			const Link& GetUpperLink() const { return m_Upper; }
			const Link& GetFootLink() const { return m_Foot; }
			const Link& GetBaseLink() const { return m_Upper.GetParent(); }
			Model& GetModel();
			Side GetSide() const { return m_Side; }
			const Area& GetArea() const { return m_Side == LeftSide ? Area::LEFT_LEG : Area::RIGHT_LEG; }
			size_t GetIndex() const { return m_Index; }
			size_t GetRank() const { return m_Rank; }
			const String& GetName() const override { return m_Name; }

			virtual Vec3 GetContactForce() const;
			Real GetLoad() const;
			Real MeasureLength() const;

		private:
			mutable Real m_ForceToLoadFactor; // constant kept for premature optimization of GetLoad();
			size_t m_Index;
			Side m_Side; // TODO: use area instead of side
			size_t m_Rank;
			Link& m_Foot;
			Link& m_Upper;
			String m_Name;
		};
	}
}
