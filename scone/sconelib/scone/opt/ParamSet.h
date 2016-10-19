#pragma once

#include "scone/core/core.h"
#include "ParamInfo.h"
#include <vector>
#include <map>

#define INIT_PARAM( PROP_, PAR_, VAR_, DEFAULT_ ) \
	VAR_ = PAR_.TryGet( GetCleanVarName( #VAR_ ), PROP_, GetCleanVarName( #VAR_ ), DEFAULT_ )

#define INIT_PARAM_NAMED( PROP_, PAR_, VAR_, NAME_, DEFAULT_ ) \
	VAR_ = PAR_.TryGet( NAME_, PROP_, NAME_, DEFAULT_ )

#define INIT_PARAM_REQUIRED( PROP_, PAR_, VAR_ ) \
	VAR_ = PAR_.Get( GetCleanVarName( #VAR_ ), PROP_, GetCleanVarName( #VAR_ ) )

#define INIT_PARAM_NAMED_REQUIRED( PROP_, PAR_, VAR_, NAME_, DEFAULT_ ) \
	VAR_ = PAR_.Get( NAME_, PROP_, NAME_ )

namespace scone
{
	namespace opt
	{
		class SCONE_API ParamSet
		{
		public:
			enum Mode { ConstructionMode, UpdateMode };
			ParamSet( Mode m = ConstructionMode ) : m_Mode( m ) { };
			ParamSet( const String& filename );
			virtual ~ParamSet() { };

			double Get( const ParamInfo& info );
			double Get( const String& name, const PropNode& props, const String node_name );
			double TryGet( const String& name, const PropNode& props, const String node_name, double default_value );
			double GetMeanStd( const String& name, double init_mean, double init_std, double min, double max );
			double GetMinMax( const String& name, double init_min, double init_max, double min, double max );

			bool Empty() { return m_Params.empty(); }
			bool CheckValues();
			void ClampValues();
			void InitRandom();

			size_t GetParamCount() const { return m_Params.size(); }
			const ParamInfo& GetParamInfo( Index idx ) { return m_Params[ idx ].first; }

			void UpdateMeanStd( const std::vector< ParamSet >& parsets );
			void UpdateMeanStd( const std::vector< double >& means, const std::vector< double >& stds );

			size_t GetFreeParamCount();
			std::vector< double > GetFreeParamValues();
			void SetFreeParamValues( std::vector< double >& values );

			template< typename Iter > bool CheckFreeParamValues( Iter b, Iter e ) {
				for ( auto iter = m_Params.begin(); iter != m_Params.end() && b != e; ++iter ) {
					if ( iter->first.is_free )
					{ if ( !iter->first.CheckValue( *b ) ) return false; else ++b; }
				}
				return true;
			}

			template< typename Iter > void ClampFreeParamValues( Iter b, Iter e ) {
				for ( auto iter = m_Params.begin(); iter != m_Params.end() && b != e; ++iter )
				{ if ( iter->first.is_free ) iter->first.ClampValue( *b++ ); }
			}

			void SetMode( Mode m ) { m_Mode = m; }
			bool IsInConstructionMode() { return m_Mode == ConstructionMode; }

			void Write( const String& filename ) const;
			void Read( const String& filename );

			std::ostream& ToStream( std::ostream& str ) const;
			std::istream& FromStream( std::istream& str, bool log_results = false );

			void PushNamePrefix( const String& prefix );
			void PopNamePrefix();
			String GetNamePrefix() const;

		private:
			Mode m_Mode;
			std::vector< std::pair< ParamInfo, double > > m_Params;
			std::vector< std::pair< ParamInfo, double > >::iterator FindParamByName( const String& name );

			// current name prefixes
			std::vector< String > m_NamePrefixes;
		};

		class SCONE_API ScopedParamSetPrefixer
		{
		public:
			ScopedParamSetPrefixer( ParamSet& par, const String& prefix ) : m_ParamSet( par ) { m_ParamSet.PushNamePrefix( prefix ); }
			~ScopedParamSetPrefixer() { m_ParamSet.PopNamePrefix(); }
		private:
			ParamSet& m_ParamSet;
		};

		class SCONE_API Parameterizable
		{
		public:
			Parameterizable() { };
			virtual ~Parameterizable() { };

			virtual void ProcessParameters( opt::ParamSet& par ) = 0;
		};

		inline std::ostream& operator<<( std::ostream& str, const ParamSet& par ) { return par.ToStream( str ); }
		inline std::istream& operator>>( std::istream& str, ParamSet& par ) { return par.FromStream( str ); }
	}
}
