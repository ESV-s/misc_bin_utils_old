// Генерируется компилятором буфера протокола.  НЕ РЕДАКТИРОВАТЬ!
// source: binexport2.proto

#include "third_party/zynamics/binexport/binexport2.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_BinExport2_BasicBlock_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_BasicBlock_IndexRange_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<2> scc_info_BinExport2_CallGraph_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_CallGraph_Edge_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_CallGraph_Vertex_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Comment_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_DataReference_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Expression_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_BinExport2_FlowGraph_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_FlowGraph_Edge_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Instruction_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Library_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Meta_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Mnemonic_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Module_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Operand_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Reference_binexport2_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_binexport2_2eproto::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Section_binexport2_2eproto;
class BinExport2_MetaDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_Meta> _instance;
} _BinExport2_Meta_default_instance_;
class BinExport2_CallGraph_VertexDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_CallGraph_Vertex> _instance;
} _BinExport2_CallGraph_Vertex_default_instance_;
class BinExport2_CallGraph_EdgeDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_CallGraph_Edge> _instance;
} _BinExport2_CallGraph_Edge_default_instance_;
class BinExport2_CallGraphDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_CallGraph> _instance;
} _BinExport2_CallGraph_default_instance_;
class BinExport2_ExpressionDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_Expression> _instance;
} _BinExport2_Expression_default_instance_;
class BinExport2_OperandDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_Operand> _instance;
} _BinExport2_Operand_default_instance_;
class BinExport2_MnemonicDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_Mnemonic> _instance;
} _BinExport2_Mnemonic_default_instance_;
class BinExport2_InstructionDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_Instruction> _instance;
} _BinExport2_Instruction_default_instance_;
class BinExport2_BasicBlock_IndexRangeDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_BasicBlock_IndexRange> _instance;
} _BinExport2_BasicBlock_IndexRange_default_instance_;
class BinExport2_BasicBlockDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_BasicBlock> _instance;
} _BinExport2_BasicBlock_default_instance_;
class BinExport2_FlowGraph_EdgeDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_FlowGraph_Edge> _instance;
} _BinExport2_FlowGraph_Edge_default_instance_;
class BinExport2_FlowGraphDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_FlowGraph> _instance;
} _BinExport2_FlowGraph_default_instance_;
class BinExport2_ReferenceDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_Reference> _instance;
} _BinExport2_Reference_default_instance_;
class BinExport2_DataReferenceDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_DataReference> _instance;
} _BinExport2_DataReference_default_instance_;
class BinExport2_CommentDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_Comment> _instance;
} _BinExport2_Comment_default_instance_;
class BinExport2_SectionDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_Section> _instance;
} _BinExport2_Section_default_instance_;
class BinExport2_LibraryDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_Library> _instance;
} _BinExport2_Library_default_instance_;
class BinExport2_ModuleDefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2_Module> _instance;
} _BinExport2_Module_default_instance_;
class BinExport2DefaultTypeInternal {
public:
	::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<BinExport2> _instance;
} _BinExport2_default_instance_;
static void InitDefaultsscc_info_BinExport2_binexport2_2eproto() {
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	{
		void* ptr = &::_BinExport2_default_instance_;
		new (ptr) ::BinExport2();
		::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
	}
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<14> scc_info_BinExport2_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 14, 0, InitDefaultsscc_info_BinExport2_binexport2_2eproto },{
		&scc_info_BinExport2_Meta_binexport2_2eproto.base,
		&scc_info_BinExport2_Expression_binexport2_2eproto.base,
		&scc_info_BinExport2_Operand_binexport2_2eproto.base,
		&scc_info_BinExport2_Mnemonic_binexport2_2eproto.base,
		&scc_info_BinExport2_Instruction_binexport2_2eproto.base,
		&scc_info_BinExport2_BasicBlock_binexport2_2eproto.base,
		&scc_info_BinExport2_FlowGraph_binexport2_2eproto.base,
		&scc_info_BinExport2_CallGraph_binexport2_2eproto.base,
		&scc_info_BinExport2_Reference_binexport2_2eproto.base,
		&scc_info_BinExport2_Comment_binexport2_2eproto.base,
		&scc_info_BinExport2_Section_binexport2_2eproto.base,
		&scc_info_BinExport2_Library_binexport2_2eproto.base,
		&scc_info_BinExport2_DataReference_binexport2_2eproto.base,
		&scc_info_BinExport2_Module_binexport2_2eproto.base, } };

	static void InitDefaultsscc_info_BinExport2_BasicBlock_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_BasicBlock_default_instance_;
			new (ptr) ::BinExport2_BasicBlock();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_BinExport2_BasicBlock_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_BinExport2_BasicBlock_binexport2_2eproto },{
		&scc_info_BinExport2_BasicBlock_IndexRange_binexport2_2eproto.base, } };

	static void InitDefaultsscc_info_BinExport2_BasicBlock_IndexRange_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_BasicBlock_IndexRange_default_instance_;
			new (ptr) ::BinExport2_BasicBlock_IndexRange();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_BasicBlock_IndexRange_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_BasicBlock_IndexRange_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_CallGraph_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_CallGraph_default_instance_;
			new (ptr) ::BinExport2_CallGraph();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<2> scc_info_BinExport2_CallGraph_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 2, 0, InitDefaultsscc_info_BinExport2_CallGraph_binexport2_2eproto },{
		&scc_info_BinExport2_CallGraph_Vertex_binexport2_2eproto.base,
		&scc_info_BinExport2_CallGraph_Edge_binexport2_2eproto.base, } };

	static void InitDefaultsscc_info_BinExport2_CallGraph_Edge_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_CallGraph_Edge_default_instance_;
			new (ptr) ::BinExport2_CallGraph_Edge();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_CallGraph_Edge_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_CallGraph_Edge_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_CallGraph_Vertex_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_CallGraph_Vertex_default_instance_;
			new (ptr) ::BinExport2_CallGraph_Vertex();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_CallGraph_Vertex_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_CallGraph_Vertex_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_Comment_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_Comment_default_instance_;
			new (ptr) ::BinExport2_Comment();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Comment_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_Comment_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_DataReference_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_DataReference_default_instance_;
			new (ptr) ::BinExport2_DataReference();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_DataReference_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_DataReference_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_Expression_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_Expression_default_instance_;
			new (ptr) ::BinExport2_Expression();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Expression_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_Expression_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_FlowGraph_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_FlowGraph_default_instance_;
			new (ptr) ::BinExport2_FlowGraph();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_BinExport2_FlowGraph_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_BinExport2_FlowGraph_binexport2_2eproto },{
		&scc_info_BinExport2_FlowGraph_Edge_binexport2_2eproto.base, } };

	static void InitDefaultsscc_info_BinExport2_FlowGraph_Edge_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_FlowGraph_Edge_default_instance_;
			new (ptr) ::BinExport2_FlowGraph_Edge();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_FlowGraph_Edge_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_FlowGraph_Edge_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_Instruction_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_Instruction_default_instance_;
			new (ptr) ::BinExport2_Instruction();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Instruction_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_Instruction_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_Library_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_Library_default_instance_;
			new (ptr) ::BinExport2_Library();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Library_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_Library_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_Meta_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_Meta_default_instance_;
			new (ptr) ::BinExport2_Meta();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Meta_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_Meta_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_Mnemonic_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_Mnemonic_default_instance_;
			new (ptr) ::BinExport2_Mnemonic();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Mnemonic_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_Mnemonic_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_Module_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_Module_default_instance_;
			new (ptr) ::BinExport2_Module();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Module_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_Module_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_Operand_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_Operand_default_instance_;
			new (ptr) ::BinExport2_Operand();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Operand_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_Operand_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_Reference_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_Reference_default_instance_;
			new (ptr) ::BinExport2_Reference();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Reference_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_Reference_binexport2_2eproto },{} };

	static void InitDefaultsscc_info_BinExport2_Section_binexport2_2eproto() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void* ptr = &::_BinExport2_Section_default_instance_;
			new (ptr) ::BinExport2_Section();
			::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
		}
	}

	::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_BinExport2_Section_binexport2_2eproto =
	{ { ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_BinExport2_Section_binexport2_2eproto },{} };

	static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_binexport2_2eproto[19];
	static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_binexport2_2eproto[4];
	static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_binexport2_2eproto = nullptr;

	const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_binexport2_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
		PROTOBUF_FIELD_OFFSET(::BinExport2_Meta, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Meta, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Meta, executable_name_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Meta, executable_id_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Meta, architecture_name_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Meta, timestamp_),
		0,
		1,
		2,
		3,
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Vertex, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Vertex, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Vertex, address_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Vertex, type_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Vertex, mangled_name_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Vertex, demangled_name_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Vertex, library_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Vertex, module_index_),
		2,
		3,
		0,
		1,
		4,
		5,
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Edge, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Edge, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Edge, source_vertex_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph_Edge, target_vertex_index_),
		0,
		1,
		~0u,  // no _has_bits_
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph, vertex_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_CallGraph, edge_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Expression, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Expression, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Expression, type_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Expression, symbol_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Expression, immediate_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Expression, parent_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Expression, is_relocation_),
		4,
		0,
		1,
		2,
		3,
		~0u,  // no _has_bits_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Operand, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Operand, expression_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Mnemonic, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Mnemonic, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Mnemonic, name_),
		0,
		PROTOBUF_FIELD_OFFSET(::BinExport2_Instruction, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Instruction, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Instruction, address_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Instruction, call_target_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Instruction, mnemonic_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Instruction, operand_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Instruction, raw_bytes_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Instruction, comment_index_),
		1,
		~0u,
		2,
		~0u,
		0,
		~0u,
		PROTOBUF_FIELD_OFFSET(::BinExport2_BasicBlock_IndexRange, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_BasicBlock_IndexRange, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_BasicBlock_IndexRange, begin_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_BasicBlock_IndexRange, end_index_),
		0,
		1,
		~0u,  // no _has_bits_
		PROTOBUF_FIELD_OFFSET(::BinExport2_BasicBlock, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_BasicBlock, instruction_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph_Edge, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph_Edge, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph_Edge, source_basic_block_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph_Edge, target_basic_block_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph_Edge, type_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph_Edge, is_back_edge_),
		0,
		1,
		3,
		2,
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph, basic_block_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph, entry_basic_block_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_FlowGraph, edge_),
		~0u,
		0,
		~0u,
		PROTOBUF_FIELD_OFFSET(::BinExport2_Reference, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Reference, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Reference, instruction_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Reference, instruction_operand_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Reference, operand_expression_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Reference, string_table_index_),
		0,
		1,
		2,
		3,
		PROTOBUF_FIELD_OFFSET(::BinExport2_DataReference, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_DataReference, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_DataReference, instruction_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_DataReference, address_),
		1,
		0,
		PROTOBUF_FIELD_OFFSET(::BinExport2_Comment, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Comment, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Comment, instruction_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Comment, instruction_operand_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Comment, operand_expression_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Comment, string_table_index_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Comment, repeatable_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Comment, type_),
		0,
		1,
		2,
		3,
		4,
		5,
		PROTOBUF_FIELD_OFFSET(::BinExport2_Section, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Section, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Section, address_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Section, size_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Section, flag_r_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Section, flag_w_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Section, flag_x_),
		0,
		1,
		2,
		3,
		4,
		PROTOBUF_FIELD_OFFSET(::BinExport2_Library, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Library, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Library, is_static_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Library, load_address_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Library, name_),
		2,
		1,
		0,
		PROTOBUF_FIELD_OFFSET(::BinExport2_Module, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2_Module, _internal_metadata_),
		~0u,  // no _extensions_
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2_Module, name_),
		0,
		PROTOBUF_FIELD_OFFSET(::BinExport2, _has_bits_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, _internal_metadata_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, _extensions_),
		~0u,  // no _oneof_case_
		~0u,  // no _weak_field_map_
		PROTOBUF_FIELD_OFFSET(::BinExport2, meta_information_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, expression_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, operand_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, mnemonic_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, instruction_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, basic_block_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, flow_graph_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, call_graph_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, string_table_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, address_comment_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, comment_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, string_reference_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, expression_substitution_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, section_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, library_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, data_reference_),
		PROTOBUF_FIELD_OFFSET(::BinExport2, module_),
		0,
		~0u,
		~0u,
		~0u,
		~0u,
		~0u,
		~0u,
		1,
		~0u,
		~0u,
		~0u,
		~0u,
		~0u,
		~0u,
		~0u,
		~0u,
		~0u,
	};
	static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
		{ 0, 9, sizeof(::BinExport2_Meta) },
		{ 13, 24, sizeof(::BinExport2_CallGraph_Vertex) },
		{ 30, 37, sizeof(::BinExport2_CallGraph_Edge) },
		{ 39, -1, sizeof(::BinExport2_CallGraph) },
		{ 46, 56, sizeof(::BinExport2_Expression) },
		{ 61, -1, sizeof(::BinExport2_Operand) },
		{ 67, 73, sizeof(::BinExport2_Mnemonic) },
		{ 74, 85, sizeof(::BinExport2_Instruction) },
		{ 91, 98, sizeof(::BinExport2_BasicBlock_IndexRange) },
		{ 100, -1, sizeof(::BinExport2_BasicBlock) },
		{ 106, 115, sizeof(::BinExport2_FlowGraph_Edge) },
		{ 119, 127, sizeof(::BinExport2_FlowGraph) },
		{ 130, 139, sizeof(::BinExport2_Reference) },
		{ 143, 150, sizeof(::BinExport2_DataReference) },
		{ 152, 163, sizeof(::BinExport2_Comment) },
		{ 169, 179, sizeof(::BinExport2_Section) },
		{ 184, 192, sizeof(::BinExport2_Library) },
		{ 195, 201, sizeof(::BinExport2_Module) },
		{ 202, 224, sizeof(::BinExport2) },
	};

	static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_Meta_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_CallGraph_Vertex_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_CallGraph_Edge_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_CallGraph_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_Expression_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_Operand_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_Mnemonic_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_Instruction_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_BasicBlock_IndexRange_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_BasicBlock_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_FlowGraph_Edge_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_FlowGraph_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_Reference_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_DataReference_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_Comment_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_Section_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_Library_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_Module_default_instance_),
		reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_BinExport2_default_instance_),
	};

	const char descriptor_table_protodef_binexport2_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
		"\n\020binexport2.proto\"\245\027\n\nBinExport2\022*\n\020met"
		"a_information\030\001 \001(\0132\020.BinExport2.Meta\022*\n"
		"\nexpression\030\002 \003(\0132\026.BinExport2.Expressio"
		"n\022$\n\007operand\030\003 \003(\0132\023.BinExport2.Operand\022"
		"&\n\010mnemonic\030\004 \003(\0132\024.BinExport2.Mnemonic\022"
		",\n\013instruction\030\005 \003(\0132\027.BinExport2.Instru"
		"ction\022+\n\013basic_block\030\006 \003(\0132\026.BinExport2."
		"BasicBlock\022)\n\nflow_graph\030\007 \003(\0132\025.BinExpo"
		"rt2.FlowGraph\022)\n\ncall_graph\030\010 \001(\0132\025.BinE"
		"xport2.CallGraph\022\024\n\014string_table\030\t \003(\t\0222"
		"\n\017address_comment\030\n \003(\0132\025.BinExport2.Ref"
		"erenceB\002\030\001\022$\n\007comment\030\021 \003(\0132\023.BinExport2"
		".Comment\022/\n\020string_reference\030\013 \003(\0132\025.Bin"
		"Export2.Reference\0226\n\027expression_substitu"
		"tion\030\014 \003(\0132\025.BinExport2.Reference\022$\n\007sec"
		"tion\030\r \003(\0132\023.BinExport2.Section\022$\n\007libra"
		"ry\030\016 \003(\0132\023.BinExport2.Library\0221\n\016data_re"
		"ference\030\017 \003(\0132\031.BinExport2.DataReference"
		"\022\"\n\006module\030\020 \003(\0132\022.BinExport2.Module\032j\n\004"
		"Meta\022\027\n\017executable_name\030\001 \001(\t\022\025\n\rexecuta"
		"ble_id\030\002 \001(\t\022\031\n\021architecture_name\030\003 \001(\t\022"
		"\021\n\ttimestamp\030\004 \001(\003J\004\010\005\020\006\032\234\003\n\tCallGraph\022,"
		"\n\006vertex\030\001 \003(\0132\034.BinExport2.CallGraph.Ve"
		"rtex\022(\n\004edge\030\002 \003(\0132\032.BinExport2.CallGrap"
		"h.Edge\032\364\001\n\006Vertex\022\017\n\007address\030\001 \001(\004\0227\n\004ty"
		"pe\030\002 \001(\0162!.BinExport2.CallGraph.Vertex.T"
		"ype:\006NORMAL\022\024\n\014mangled_name\030\003 \001(\t\022\026\n\016dem"
		"angled_name\030\004 \001(\t\022\025\n\rlibrary_index\030\005 \001(\005"
		"\022\024\n\014module_index\030\006 \001(\005\"E\n\004Type\022\n\n\006NORMAL"
		"\020\000\022\013\n\007LIBRARY\020\001\022\014\n\010IMPORTED\020\002\022\t\n\005THUNK\020\003"
		"\022\013\n\007INVALID\020\004\032@\n\004Edge\022\033\n\023source_vertex_i"
		"ndex\030\001 \001(\005\022\033\n\023target_vertex_index\030\002 \001(\005\032"
		"\220\002\n\nExpression\0228\n\004type\030\001 \001(\0162\033.BinExport"
		"2.Expression.Type:\rIMMEDIATE_INT\022\016\n\006symb"
		"ol\030\002 \001(\t\022\021\n\timmediate\030\003 \001(\004\022\024\n\014parent_in"
		"dex\030\004 \001(\005\022\025\n\ris_relocation\030\005 \001(\010\"x\n\004Type"
		"\022\n\n\006SYMBOL\020\001\022\021\n\rIMMEDIATE_INT\020\002\022\023\n\017IMMED"
		"IATE_FLOAT\020\003\022\014\n\010OPERATOR\020\004\022\014\n\010REGISTER\020\005"
		"\022\017\n\013SIZE_PREFIX\020\006\022\017\n\013DEREFERENCE\020\007\032#\n\007Op"
		"erand\022\030\n\020expression_index\030\001 \003(\005\032\030\n\010Mnemo"
		"nic\022\014\n\004name\030\001 \001(\t\032\217\001\n\013Instruction\022\017\n\007add"
		"ress\030\001 \001(\004\022\023\n\013call_target\030\002 \003(\004\022\031\n\016mnemo"
		"nic_index\030\003 \001(\005:\0010\022\025\n\roperand_index\030\004 \003("
		"\005\022\021\n\traw_bytes\030\005 \001(\014\022\025\n\rcomment_index\030\006 "
		"\003(\005\032\200\001\n\nBasicBlock\022<\n\021instruction_index\030"
		"\001 \003(\0132!.BinExport2.BasicBlock.IndexRange"
		"\0324\n\nIndexRange\022\023\n\013begin_index\030\001 \001(\005\022\021\n\te"
		"nd_index\030\002 \001(\005\032\351\002\n\tFlowGraph\022\031\n\021basic_bl"
		"ock_index\030\001 \003(\005\022\037\n\027entry_basic_block_ind"
		"ex\030\003 \001(\005\022(\n\004edge\030\002 \003(\0132\032.BinExport2.Flow"
		"Graph.Edge\032\365\001\n\004Edge\022 \n\030source_basic_bloc"
		"k_index\030\001 \001(\005\022 \n\030target_basic_block_inde"
		"x\030\002 \001(\005\022<\n\004type\030\003 \001(\0162\037.BinExport2.FlowG"
		"raph.Edge.Type:\rUNCONDITIONAL\022\033\n\014is_back"
		"_edge\030\004 \001(\010:\005false\"N\n\004Type\022\022\n\016CONDITION_"
		"TRUE\020\001\022\023\n\017CONDITION_FALSE\020\002\022\021\n\rUNCONDITI"
		"ONAL\020\003\022\n\n\006SWITCH\020\004\032\215\001\n\tReference\022\031\n\021inst"
		"ruction_index\030\001 \001(\005\022$\n\031instruction_opera"
		"nd_index\030\002 \001(\005:\0010\022#\n\030operand_expression_"
		"index\030\003 \001(\005:\0010\022\032\n\022string_table_index\030\004 \001"
		"(\005\032;\n\rDataReference\022\031\n\021instruction_index"
		"\030\001 \001(\005\022\017\n\007address\030\002 \001(\004\032\324\002\n\007Comment\022\031\n\021i"
		"nstruction_index\030\001 \001(\005\022$\n\031instruction_op"
		"erand_index\030\002 \001(\005:\0010\022#\n\030operand_expressi"
		"on_index\030\003 \001(\005:\0010\022\032\n\022string_table_index\030"
		"\004 \001(\005\022\022\n\nrepeatable\030\005 \001(\010\022/\n\004type\030\006 \001(\0162"
		"\030.BinExport2.Comment.Type:\007DEFAULT\"\201\001\n\004T"
		"ype\022\013\n\007DEFAULT\020\000\022\014\n\010ANTERIOR\020\001\022\r\n\tPOSTER"
		"IOR\020\002\022\014\n\010FUNCTION\020\003\022\010\n\004ENUM\020\004\022\014\n\010LOCATIO"
		"N\020\005\022\024\n\020GLOBAL_REFERENCE\020\006\022\023\n\017LOCAL_REFER"
		"ENCE\020\007\032X\n\007Section\022\017\n\007address\030\001 \001(\004\022\014\n\004si"
		"ze\030\002 \001(\004\022\016\n\006flag_r\030\003 \001(\010\022\016\n\006flag_w\030\004 \001(\010"
		"\022\016\n\006flag_x\030\005 \001(\010\032C\n\007Library\022\021\n\tis_static"
		"\030\001 \001(\010\022\027\n\014load_address\030\002 \001(\004:\0010\022\014\n\004name\030"
		"\003 \001(\t\032\026\n\006Module\022\014\n\004name\030\001 \001(\t*\013\010\200\302\327/\020\200\200\200"
		"\200\002B)\n\034com.google.security.zynamicsB\tBinE"
		"xport"
		;
	static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_binexport2_2eproto_deps[1] = {
	};
	static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_binexport2_2eproto_sccs[19] = {
		&scc_info_BinExport2_binexport2_2eproto.base,
		&scc_info_BinExport2_BasicBlock_binexport2_2eproto.base,
		&scc_info_BinExport2_BasicBlock_IndexRange_binexport2_2eproto.base,
		&scc_info_BinExport2_CallGraph_binexport2_2eproto.base,
		&scc_info_BinExport2_CallGraph_Edge_binexport2_2eproto.base,
		&scc_info_BinExport2_CallGraph_Vertex_binexport2_2eproto.base,
		&scc_info_BinExport2_Comment_binexport2_2eproto.base,
		&scc_info_BinExport2_DataReference_binexport2_2eproto.base,
		&scc_info_BinExport2_Expression_binexport2_2eproto.base,
		&scc_info_BinExport2_FlowGraph_binexport2_2eproto.base,
		&scc_info_BinExport2_FlowGraph_Edge_binexport2_2eproto.base,
		&scc_info_BinExport2_Instruction_binexport2_2eproto.base,
		&scc_info_BinExport2_Library_binexport2_2eproto.base,
		&scc_info_BinExport2_Meta_binexport2_2eproto.base,
		&scc_info_BinExport2_Mnemonic_binexport2_2eproto.base,
		&scc_info_BinExport2_Module_binexport2_2eproto.base,
		&scc_info_BinExport2_Operand_binexport2_2eproto.base,
		&scc_info_BinExport2_Reference_binexport2_2eproto.base,
		&scc_info_BinExport2_Section_binexport2_2eproto.base,
	};
	static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_binexport2_2eproto_once;
	const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_binexport2_2eproto = {
		false, false, descriptor_table_protodef_binexport2_2eproto, "binexport2.proto", 3045,
		&descriptor_table_binexport2_2eproto_once, descriptor_table_binexport2_2eproto_sccs, descriptor_table_binexport2_2eproto_deps, 19, 0,
		schemas, file_default_instances, TableStruct_binexport2_2eproto::offsets,
		file_level_metadata_binexport2_2eproto, 19, file_level_enum_descriptors_binexport2_2eproto, file_level_service_descriptors_binexport2_2eproto,
	};

	// Force running AddDescriptors() at dynamic initialization time.
	PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_binexport2_2eproto(&descriptor_table_binexport2_2eproto);
	const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* BinExport2_CallGraph_Vertex_Type_descriptor() {
		::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_binexport2_2eproto);
		return file_level_enum_descriptors_binexport2_2eproto[0];
	}
	bool BinExport2_CallGraph_Vertex_Type_IsValid(int value) {
		switch (value) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			return true;
		default:
			return false;
		}
	}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
	constexpr BinExport2_CallGraph_Vertex_Type BinExport2_CallGraph_Vertex::NORMAL;
	constexpr BinExport2_CallGraph_Vertex_Type BinExport2_CallGraph_Vertex::LIBRARY;
	constexpr BinExport2_CallGraph_Vertex_Type BinExport2_CallGraph_Vertex::IMPORTED;
	constexpr BinExport2_CallGraph_Vertex_Type BinExport2_CallGraph_Vertex::THUNK;
	constexpr BinExport2_CallGraph_Vertex_Type BinExport2_CallGraph_Vertex::INVALID;
	constexpr BinExport2_CallGraph_Vertex_Type BinExport2_CallGraph_Vertex::Type_MIN;
	constexpr BinExport2_CallGraph_Vertex_Type BinExport2_CallGraph_Vertex::Type_MAX;
	constexpr int BinExport2_CallGraph_Vertex::Type_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
	const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* BinExport2_Expression_Type_descriptor() {
		::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_binexport2_2eproto);
		return file_level_enum_descriptors_binexport2_2eproto[1];
	}
	bool BinExport2_Expression_Type_IsValid(int value) {
		switch (value) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return true;
		default:
			return false;
		}
	}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
	constexpr BinExport2_Expression_Type BinExport2_Expression::SYMBOL;
	constexpr BinExport2_Expression_Type BinExport2_Expression::IMMEDIATE_INT;
	constexpr BinExport2_Expression_Type BinExport2_Expression::IMMEDIATE_FLOAT;
	constexpr BinExport2_Expression_Type BinExport2_Expression::OPERATOR;
	constexpr BinExport2_Expression_Type BinExport2_Expression::REGISTER;
	constexpr BinExport2_Expression_Type BinExport2_Expression::SIZE_PREFIX;
	constexpr BinExport2_Expression_Type BinExport2_Expression::DEREFERENCE;
	constexpr BinExport2_Expression_Type BinExport2_Expression::Type_MIN;
	constexpr BinExport2_Expression_Type BinExport2_Expression::Type_MAX;
	constexpr int BinExport2_Expression::Type_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
	const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* BinExport2_FlowGraph_Edge_Type_descriptor() {
		::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_binexport2_2eproto);
		return file_level_enum_descriptors_binexport2_2eproto[2];
	}
	bool BinExport2_FlowGraph_Edge_Type_IsValid(int value) {
		switch (value) {
		case 1:
		case 2:
		case 3:
		case 4:
			return true;
		default:
			return false;
		}
	}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
	constexpr BinExport2_FlowGraph_Edge_Type BinExport2_FlowGraph_Edge::CONDITION_TRUE;
	constexpr BinExport2_FlowGraph_Edge_Type BinExport2_FlowGraph_Edge::CONDITION_FALSE;
	constexpr BinExport2_FlowGraph_Edge_Type BinExport2_FlowGraph_Edge::UNCONDITIONAL;
	constexpr BinExport2_FlowGraph_Edge_Type BinExport2_FlowGraph_Edge::SWITCH;
	constexpr BinExport2_FlowGraph_Edge_Type BinExport2_FlowGraph_Edge::Type_MIN;
	constexpr BinExport2_FlowGraph_Edge_Type BinExport2_FlowGraph_Edge::Type_MAX;
	constexpr int BinExport2_FlowGraph_Edge::Type_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
	const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* BinExport2_Comment_Type_descriptor() {
		::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_binexport2_2eproto);
		return file_level_enum_descriptors_binexport2_2eproto[3];
	}
	bool BinExport2_Comment_Type_IsValid(int value) {
		switch (value) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return true;
		default:
			return false;
		}
	}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
	constexpr BinExport2_Comment_Type BinExport2_Comment::DEFAULT;
	constexpr BinExport2_Comment_Type BinExport2_Comment::ANTERIOR;
	constexpr BinExport2_Comment_Type BinExport2_Comment::POSTERIOR;
	constexpr BinExport2_Comment_Type BinExport2_Comment::FUNCTION;
	constexpr BinExport2_Comment_Type BinExport2_Comment::ENUM;
	constexpr BinExport2_Comment_Type BinExport2_Comment::LOCATION;
	constexpr BinExport2_Comment_Type BinExport2_Comment::GLOBAL_REFERENCE;
	constexpr BinExport2_Comment_Type BinExport2_Comment::LOCAL_REFERENCE;
	constexpr BinExport2_Comment_Type BinExport2_Comment::Type_MIN;
	constexpr BinExport2_Comment_Type BinExport2_Comment::Type_MAX;
	constexpr int BinExport2_Comment::Type_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

	// ===================================================================

	class BinExport2_Meta::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_Meta>()._has_bits_);
		static void set_has_executable_name(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
		static void set_has_executable_id(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
		static void set_has_architecture_name(HasBits* has_bits) {
			(*has_bits)[0] |= 4u;
		}
		static void set_has_timestamp(HasBits* has_bits) {
			(*has_bits)[0] |= 8u;
		}
	};

	BinExport2_Meta::BinExport2_Meta(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.Meta)
	}
	BinExport2_Meta::BinExport2_Meta(const BinExport2_Meta& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		executable_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		if (from._internal_has_executable_name()) {
			executable_name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_executable_name(),
				GetArena());
		}
		executable_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		if (from._internal_has_executable_id()) {
			executable_id_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_executable_id(),
				GetArena());
		}
		architecture_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		if (from._internal_has_architecture_name()) {
			architecture_name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_architecture_name(),
				GetArena());
		}
		timestamp_ = from.timestamp_;
		// @@protoc_insertion_point(copy_constructor:BinExport2.Meta)
	}

	void BinExport2_Meta::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_Meta_binexport2_2eproto.base);
		executable_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		executable_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		architecture_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		timestamp_ = PROTOBUF_LONGLONG(0);
	}

	BinExport2_Meta::~BinExport2_Meta() {
		// @@protoc_insertion_point(destructor:BinExport2.Meta)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_Meta::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
		executable_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		executable_id_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		architecture_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
	}

	void BinExport2_Meta::ArenaDtor(void* object) {
		BinExport2_Meta* _this = reinterpret_cast< BinExport2_Meta* >(object);
		(void)_this;
	}
	void BinExport2_Meta::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_Meta::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_Meta& BinExport2_Meta::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_Meta_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_Meta::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.Meta)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000007u) {
			if (cached_has_bits & 0x00000001u) {
				executable_name_.ClearNonDefaultToEmpty();
			}
			if (cached_has_bits & 0x00000002u) {
				executable_id_.ClearNonDefaultToEmpty();
			}
			if (cached_has_bits & 0x00000004u) {
				architecture_name_.ClearNonDefaultToEmpty();
			}
		}
		timestamp_ = PROTOBUF_LONGLONG(0);
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_Meta::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional string executable_name = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
					auto str = _internal_mutable_executable_name();
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
#ifndef NDEBUG
					::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "BinExport2.Meta.executable_name");
#endif  // !NDEBUG
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional string executable_id = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
					auto str = _internal_mutable_executable_id();
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
#ifndef NDEBUG
					::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "BinExport2.Meta.executable_id");
#endif  // !NDEBUG
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional string architecture_name = 3;
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
					auto str = _internal_mutable_architecture_name();
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
#ifndef NDEBUG
					::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "BinExport2.Meta.architecture_name");
#endif  // !NDEBUG
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int64 timestamp = 4;
			case 4:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
					_Internal::set_has_timestamp(&has_bits);
					timestamp_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_Meta::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.Meta)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional string executable_name = 1;
		if (cached_has_bits & 0x00000001u) {
			::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
				this->_internal_executable_name().data(), static_cast<int>(this->_internal_executable_name().length()),
				::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
				"BinExport2.Meta.executable_name");
			target = stream->WriteStringMaybeAliased(
				1, this->_internal_executable_name(), target);
		}

		// optional string executable_id = 2;
		if (cached_has_bits & 0x00000002u) {
			::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
				this->_internal_executable_id().data(), static_cast<int>(this->_internal_executable_id().length()),
				::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
				"BinExport2.Meta.executable_id");
			target = stream->WriteStringMaybeAliased(
				2, this->_internal_executable_id(), target);
		}

		// optional string architecture_name = 3;
		if (cached_has_bits & 0x00000004u) {
			::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
				this->_internal_architecture_name().data(), static_cast<int>(this->_internal_architecture_name().length()),
				::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
				"BinExport2.Meta.architecture_name");
			target = stream->WriteStringMaybeAliased(
				3, this->_internal_architecture_name(), target);
		}

		// optional int64 timestamp = 4;
		if (cached_has_bits & 0x00000008u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(4, this->_internal_timestamp(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.Meta)
		return target;
	}

	size_t BinExport2_Meta::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.Meta)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000000fu) {
			// optional string executable_name = 1;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
						this->_internal_executable_name());
			}

			// optional string executable_id = 2;
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
						this->_internal_executable_id());
			}

			// optional string architecture_name = 3;
			if (cached_has_bits & 0x00000004u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
						this->_internal_architecture_name());
			}

			// optional int64 timestamp = 4;
			if (cached_has_bits & 0x00000008u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
						this->_internal_timestamp());
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_Meta::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.Meta)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_Meta* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_Meta>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.Meta)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.Meta)
			MergeFrom(*source);
		}
	}

	void BinExport2_Meta::MergeFrom(const BinExport2_Meta& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.Meta)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x0000000fu) {
			if (cached_has_bits & 0x00000001u) {
				_internal_set_executable_name(from._internal_executable_name());
			}
			if (cached_has_bits & 0x00000002u) {
				_internal_set_executable_id(from._internal_executable_id());
			}
			if (cached_has_bits & 0x00000004u) {
				_internal_set_architecture_name(from._internal_architecture_name());
			}
			if (cached_has_bits & 0x00000008u) {
				timestamp_ = from.timestamp_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_Meta::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.Meta)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_Meta::CopyFrom(const BinExport2_Meta& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.Meta)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_Meta::IsInitialized() const {
		return true;
	}

	void BinExport2_Meta::InternalSwap(BinExport2_Meta* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		executable_name_.Swap(&other->executable_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
		executable_id_.Swap(&other->executable_id_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
		architecture_name_.Swap(&other->architecture_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
		swap(timestamp_, other->timestamp_);
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_Meta::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_CallGraph_Vertex::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_CallGraph_Vertex>()._has_bits_);
		static void set_has_address(HasBits* has_bits) {
			(*has_bits)[0] |= 4u;
		}
		static void set_has_type(HasBits* has_bits) {
			(*has_bits)[0] |= 8u;
		}
		static void set_has_mangled_name(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
		static void set_has_demangled_name(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
		static void set_has_library_index(HasBits* has_bits) {
			(*has_bits)[0] |= 16u;
		}
		static void set_has_module_index(HasBits* has_bits) {
			(*has_bits)[0] |= 32u;
		}
	};

	BinExport2_CallGraph_Vertex::BinExport2_CallGraph_Vertex(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.CallGraph.Vertex)
	}
	BinExport2_CallGraph_Vertex::BinExport2_CallGraph_Vertex(const BinExport2_CallGraph_Vertex& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		mangled_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		if (from._internal_has_mangled_name()) {
			mangled_name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_mangled_name(),
				GetArena());
		}
		demangled_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		if (from._internal_has_demangled_name()) {
			demangled_name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_demangled_name(),
				GetArena());
		}
		::memcpy(&address_, &from.address_,
			static_cast<size_t>(reinterpret_cast<char*>(&module_index_) -
				reinterpret_cast<char*>(&address_)) + sizeof(module_index_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.CallGraph.Vertex)
	}

	void BinExport2_CallGraph_Vertex::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_CallGraph_Vertex_binexport2_2eproto.base);
		mangled_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		demangled_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&address_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&module_index_) -
				reinterpret_cast<char*>(&address_)) + sizeof(module_index_));
	}

	BinExport2_CallGraph_Vertex::~BinExport2_CallGraph_Vertex() {
		// @@protoc_insertion_point(destructor:BinExport2.CallGraph.Vertex)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_CallGraph_Vertex::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
		mangled_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		demangled_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
	}

	void BinExport2_CallGraph_Vertex::ArenaDtor(void* object) {
		BinExport2_CallGraph_Vertex* _this = reinterpret_cast< BinExport2_CallGraph_Vertex* >(object);
		(void)_this;
	}
	void BinExport2_CallGraph_Vertex::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_CallGraph_Vertex::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_CallGraph_Vertex& BinExport2_CallGraph_Vertex::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_CallGraph_Vertex_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_CallGraph_Vertex::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.CallGraph.Vertex)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			if (cached_has_bits & 0x00000001u) {
				mangled_name_.ClearNonDefaultToEmpty();
			}
			if (cached_has_bits & 0x00000002u) {
				demangled_name_.ClearNonDefaultToEmpty();
			}
		}
		if (cached_has_bits & 0x0000003cu) {
			::memset(&address_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&module_index_) -
				reinterpret_cast<char*>(&address_)) + sizeof(module_index_));
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_CallGraph_Vertex::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional uint64 address = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					_Internal::set_has_address(&has_bits);
					address_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional .BinExport2.CallGraph.Vertex.Type type = 2 [default = NORMAL];
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
					::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
					if (PROTOBUF_PREDICT_TRUE(::BinExport2_CallGraph_Vertex_Type_IsValid(val))) {
						_internal_set_type(static_cast<::BinExport2_CallGraph_Vertex_Type>(val));
					}
					else {
						::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(2, val, mutable_unknown_fields());
					}
				}
				else goto handle_unusual;
				continue;
				// optional string mangled_name = 3;
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
					auto str = _internal_mutable_mangled_name();
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
#ifndef NDEBUG
					::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "BinExport2.CallGraph.Vertex.mangled_name");
#endif  // !NDEBUG
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional string demangled_name = 4;
			case 4:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
					auto str = _internal_mutable_demangled_name();
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
#ifndef NDEBUG
					::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "BinExport2.CallGraph.Vertex.demangled_name");
#endif  // !NDEBUG
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 library_index = 5;
			case 5:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
					_Internal::set_has_library_index(&has_bits);
					library_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 module_index = 6;
			case 6:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 48)) {
					_Internal::set_has_module_index(&has_bits);
					module_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_CallGraph_Vertex::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.CallGraph.Vertex)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional uint64 address = 1;
		if (cached_has_bits & 0x00000004u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_address(), target);
		}

		// optional .BinExport2.CallGraph.Vertex.Type type = 2 [default = NORMAL];
		if (cached_has_bits & 0x00000008u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
				2, this->_internal_type(), target);
		}

		// optional string mangled_name = 3;
		if (cached_has_bits & 0x00000001u) {
			::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
				this->_internal_mangled_name().data(), static_cast<int>(this->_internal_mangled_name().length()),
				::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
				"BinExport2.CallGraph.Vertex.mangled_name");
			target = stream->WriteStringMaybeAliased(
				3, this->_internal_mangled_name(), target);
		}

		// optional string demangled_name = 4;
		if (cached_has_bits & 0x00000002u) {
			::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
				this->_internal_demangled_name().data(), static_cast<int>(this->_internal_demangled_name().length()),
				::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
				"BinExport2.CallGraph.Vertex.demangled_name");
			target = stream->WriteStringMaybeAliased(
				4, this->_internal_demangled_name(), target);
		}

		// optional int32 library_index = 5;
		if (cached_has_bits & 0x00000010u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(5, this->_internal_library_index(), target);
		}

		// optional int32 module_index = 6;
		if (cached_has_bits & 0x00000020u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(6, this->_internal_module_index(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.CallGraph.Vertex)
		return target;
	}

	size_t BinExport2_CallGraph_Vertex::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.CallGraph.Vertex)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000003fu) {
			// optional string mangled_name = 3;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
						this->_internal_mangled_name());
			}

			// optional string demangled_name = 4;
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
						this->_internal_demangled_name());
			}

			// optional uint64 address = 1;
			if (cached_has_bits & 0x00000004u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
						this->_internal_address());
			}

			// optional .BinExport2.CallGraph.Vertex.Type type = 2 [default = NORMAL];
			if (cached_has_bits & 0x00000008u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
			}

			// optional int32 library_index = 5;
			if (cached_has_bits & 0x00000010u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_library_index());
			}

			// optional int32 module_index = 6;
			if (cached_has_bits & 0x00000020u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_module_index());
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_CallGraph_Vertex::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.CallGraph.Vertex)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_CallGraph_Vertex* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_CallGraph_Vertex>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.CallGraph.Vertex)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.CallGraph.Vertex)
			MergeFrom(*source);
		}
	}

	void BinExport2_CallGraph_Vertex::MergeFrom(const BinExport2_CallGraph_Vertex& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.CallGraph.Vertex)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x0000003fu) {
			if (cached_has_bits & 0x00000001u) {
				_internal_set_mangled_name(from._internal_mangled_name());
			}
			if (cached_has_bits & 0x00000002u) {
				_internal_set_demangled_name(from._internal_demangled_name());
			}
			if (cached_has_bits & 0x00000004u) {
				address_ = from.address_;
			}
			if (cached_has_bits & 0x00000008u) {
				type_ = from.type_;
			}
			if (cached_has_bits & 0x00000010u) {
				library_index_ = from.library_index_;
			}
			if (cached_has_bits & 0x00000020u) {
				module_index_ = from.module_index_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_CallGraph_Vertex::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.CallGraph.Vertex)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_CallGraph_Vertex::CopyFrom(const BinExport2_CallGraph_Vertex& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.CallGraph.Vertex)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_CallGraph_Vertex::IsInitialized() const {
		return true;
	}

	void BinExport2_CallGraph_Vertex::InternalSwap(BinExport2_CallGraph_Vertex* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		mangled_name_.Swap(&other->mangled_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
		demangled_name_.Swap(&other->demangled_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_CallGraph_Vertex, module_index_)
			+ sizeof(BinExport2_CallGraph_Vertex::module_index_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_CallGraph_Vertex, address_)>(
				reinterpret_cast<char*>(&address_),
				reinterpret_cast<char*>(&other->address_));
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_CallGraph_Vertex::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_CallGraph_Edge::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_CallGraph_Edge>()._has_bits_);
		static void set_has_source_vertex_index(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
		static void set_has_target_vertex_index(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
	};

	BinExport2_CallGraph_Edge::BinExport2_CallGraph_Edge(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.CallGraph.Edge)
	}
	BinExport2_CallGraph_Edge::BinExport2_CallGraph_Edge(const BinExport2_CallGraph_Edge& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::memcpy(&source_vertex_index_, &from.source_vertex_index_,
			static_cast<size_t>(reinterpret_cast<char*>(&target_vertex_index_) -
				reinterpret_cast<char*>(&source_vertex_index_)) + sizeof(target_vertex_index_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.CallGraph.Edge)
	}

	void BinExport2_CallGraph_Edge::SharedCtor() {
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&source_vertex_index_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&target_vertex_index_) -
				reinterpret_cast<char*>(&source_vertex_index_)) + sizeof(target_vertex_index_));
	}

	BinExport2_CallGraph_Edge::~BinExport2_CallGraph_Edge() {
		// @@protoc_insertion_point(destructor:BinExport2.CallGraph.Edge)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_CallGraph_Edge::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_CallGraph_Edge::ArenaDtor(void* object) {
		BinExport2_CallGraph_Edge* _this = reinterpret_cast< BinExport2_CallGraph_Edge* >(object);
		(void)_this;
	}
	void BinExport2_CallGraph_Edge::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_CallGraph_Edge::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_CallGraph_Edge& BinExport2_CallGraph_Edge::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_CallGraph_Edge_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_CallGraph_Edge::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.CallGraph.Edge)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			::memset(&source_vertex_index_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&target_vertex_index_) -
				reinterpret_cast<char*>(&source_vertex_index_)) + sizeof(target_vertex_index_));
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_CallGraph_Edge::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional int32 source_vertex_index = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					_Internal::set_has_source_vertex_index(&has_bits);
					source_vertex_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 target_vertex_index = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
					_Internal::set_has_target_vertex_index(&has_bits);
					target_vertex_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_CallGraph_Edge::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.CallGraph.Edge)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional int32 source_vertex_index = 1;
		if (cached_has_bits & 0x00000001u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_source_vertex_index(), target);
		}

		// optional int32 target_vertex_index = 2;
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_target_vertex_index(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.CallGraph.Edge)
		return target;
	}

	size_t BinExport2_CallGraph_Edge::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.CallGraph.Edge)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			// optional int32 source_vertex_index = 1;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_source_vertex_index());
			}

			// optional int32 target_vertex_index = 2;
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_target_vertex_index());
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_CallGraph_Edge::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.CallGraph.Edge)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_CallGraph_Edge* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_CallGraph_Edge>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.CallGraph.Edge)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.CallGraph.Edge)
			MergeFrom(*source);
		}
	}

	void BinExport2_CallGraph_Edge::MergeFrom(const BinExport2_CallGraph_Edge& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.CallGraph.Edge)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			if (cached_has_bits & 0x00000001u) {
				source_vertex_index_ = from.source_vertex_index_;
			}
			if (cached_has_bits & 0x00000002u) {
				target_vertex_index_ = from.target_vertex_index_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_CallGraph_Edge::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.CallGraph.Edge)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_CallGraph_Edge::CopyFrom(const BinExport2_CallGraph_Edge& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.CallGraph.Edge)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_CallGraph_Edge::IsInitialized() const {
		return true;
	}

	void BinExport2_CallGraph_Edge::InternalSwap(BinExport2_CallGraph_Edge* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_CallGraph_Edge, target_vertex_index_)
			+ sizeof(BinExport2_CallGraph_Edge::target_vertex_index_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_CallGraph_Edge, source_vertex_index_)>(
				reinterpret_cast<char*>(&source_vertex_index_),
				reinterpret_cast<char*>(&other->source_vertex_index_));
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_CallGraph_Edge::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_CallGraph::_Internal {
	public:
	};

	BinExport2_CallGraph::BinExport2_CallGraph(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena),
		vertex_(arena),
		edge_(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.CallGraph)
	}
	BinExport2_CallGraph::BinExport2_CallGraph(const BinExport2_CallGraph& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		vertex_(from.vertex_),
		edge_(from.edge_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		// @@protoc_insertion_point(copy_constructor:BinExport2.CallGraph)
	}

	void BinExport2_CallGraph::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_CallGraph_binexport2_2eproto.base);
	}

	BinExport2_CallGraph::~BinExport2_CallGraph() {
		// @@protoc_insertion_point(destructor:BinExport2.CallGraph)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_CallGraph::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_CallGraph::ArenaDtor(void* object) {
		BinExport2_CallGraph* _this = reinterpret_cast< BinExport2_CallGraph* >(object);
		(void)_this;
	}
	void BinExport2_CallGraph::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_CallGraph::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_CallGraph& BinExport2_CallGraph::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_CallGraph_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_CallGraph::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.CallGraph)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		vertex_.Clear();
		edge_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_CallGraph::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// repeated .BinExport2.CallGraph.Vertex vertex = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_vertex(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.CallGraph.Edge edge = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_edge(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_CallGraph::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.CallGraph)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		// repeated .BinExport2.CallGraph.Vertex vertex = 1;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_vertex_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(1, this->_internal_vertex(i), target, stream);
		}

		// repeated .BinExport2.CallGraph.Edge edge = 2;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_edge_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(2, this->_internal_edge(i), target, stream);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.CallGraph)
		return target;
	}

	size_t BinExport2_CallGraph::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.CallGraph)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		// repeated .BinExport2.CallGraph.Vertex vertex = 1;
		total_size += 1UL * this->_internal_vertex_size();
		for (const auto& msg : this->vertex_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.CallGraph.Edge edge = 2;
		total_size += 1UL * this->_internal_edge_size();
		for (const auto& msg : this->edge_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_CallGraph::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.CallGraph)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_CallGraph* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_CallGraph>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.CallGraph)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.CallGraph)
			MergeFrom(*source);
		}
	}

	void BinExport2_CallGraph::MergeFrom(const BinExport2_CallGraph& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.CallGraph)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		vertex_.MergeFrom(from.vertex_);
		edge_.MergeFrom(from.edge_);
	}

	void BinExport2_CallGraph::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.CallGraph)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_CallGraph::CopyFrom(const BinExport2_CallGraph& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.CallGraph)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_CallGraph::IsInitialized() const {
		return true;
	}

	void BinExport2_CallGraph::InternalSwap(BinExport2_CallGraph* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		vertex_.InternalSwap(&other->vertex_);
		edge_.InternalSwap(&other->edge_);
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_CallGraph::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_Expression::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_Expression>()._has_bits_);
		static void set_has_type(HasBits* has_bits) {
			(*has_bits)[0] |= 16u;
		}
		static void set_has_symbol(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
		static void set_has_immediate(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
		static void set_has_parent_index(HasBits* has_bits) {
			(*has_bits)[0] |= 4u;
		}
		static void set_has_is_relocation(HasBits* has_bits) {
			(*has_bits)[0] |= 8u;
		}
	};

	BinExport2_Expression::BinExport2_Expression(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.Expression)
	}
	BinExport2_Expression::BinExport2_Expression(const BinExport2_Expression& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		symbol_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		if (from._internal_has_symbol()) {
			symbol_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_symbol(),
				GetArena());
		}
		::memcpy(&immediate_, &from.immediate_,
			static_cast<size_t>(reinterpret_cast<char*>(&type_) -
				reinterpret_cast<char*>(&immediate_)) + sizeof(type_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.Expression)
	}

	void BinExport2_Expression::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_Expression_binexport2_2eproto.base);
		symbol_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&immediate_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&is_relocation_) -
				reinterpret_cast<char*>(&immediate_)) + sizeof(is_relocation_));
		type_ = 2;
	}

	BinExport2_Expression::~BinExport2_Expression() {
		// @@protoc_insertion_point(destructor:BinExport2.Expression)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_Expression::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
		symbol_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
	}

	void BinExport2_Expression::ArenaDtor(void* object) {
		BinExport2_Expression* _this = reinterpret_cast< BinExport2_Expression* >(object);
		(void)_this;
	}
	void BinExport2_Expression::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_Expression::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_Expression& BinExport2_Expression::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_Expression_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_Expression::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.Expression)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000001u) {
			symbol_.ClearNonDefaultToEmpty();
		}
		if (cached_has_bits & 0x0000001eu) {
			::memset(&immediate_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&is_relocation_) -
				reinterpret_cast<char*>(&immediate_)) + sizeof(is_relocation_));
			type_ = 2;
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_Expression::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional .BinExport2.Expression.Type type = 1 [default = IMMEDIATE_INT];
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
					if (PROTOBUF_PREDICT_TRUE(::BinExport2_Expression_Type_IsValid(val))) {
						_internal_set_type(static_cast<::BinExport2_Expression_Type>(val));
					}
					else {
						::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(1, val, mutable_unknown_fields());
					}
				}
				else goto handle_unusual;
				continue;
				// optional string symbol = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
					auto str = _internal_mutable_symbol();
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
#ifndef NDEBUG
					::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "BinExport2.Expression.symbol");
#endif  // !NDEBUG
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional uint64 immediate = 3;
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
					_Internal::set_has_immediate(&has_bits);
					immediate_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 parent_index = 4;
			case 4:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
					_Internal::set_has_parent_index(&has_bits);
					parent_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional bool is_relocation = 5;
			case 5:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
					_Internal::set_has_is_relocation(&has_bits);
					is_relocation_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_Expression::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.Expression)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional .BinExport2.Expression.Type type = 1 [default = IMMEDIATE_INT];
		if (cached_has_bits & 0x00000010u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
				1, this->_internal_type(), target);
		}

		// optional string symbol = 2;
		if (cached_has_bits & 0x00000001u) {
			::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
				this->_internal_symbol().data(), static_cast<int>(this->_internal_symbol().length()),
				::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
				"BinExport2.Expression.symbol");
			target = stream->WriteStringMaybeAliased(
				2, this->_internal_symbol(), target);
		}

		// optional uint64 immediate = 3;
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(3, this->_internal_immediate(), target);
		}

		// optional int32 parent_index = 4;
		if (cached_has_bits & 0x00000004u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(4, this->_internal_parent_index(), target);
		}

		// optional bool is_relocation = 5;
		if (cached_has_bits & 0x00000008u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(5, this->_internal_is_relocation(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.Expression)
		return target;
	}

	size_t BinExport2_Expression::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.Expression)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000001fu) {
			// optional string symbol = 2;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
						this->_internal_symbol());
			}

			// optional uint64 immediate = 3;
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
						this->_internal_immediate());
			}

			// optional int32 parent_index = 4;
			if (cached_has_bits & 0x00000004u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_parent_index());
			}

			// optional bool is_relocation = 5;
			if (cached_has_bits & 0x00000008u) {
				total_size += 1 + 1;
			}

			// optional .BinExport2.Expression.Type type = 1 [default = IMMEDIATE_INT];
			if (cached_has_bits & 0x00000010u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_Expression::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.Expression)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_Expression* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_Expression>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.Expression)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.Expression)
			MergeFrom(*source);
		}
	}

	void BinExport2_Expression::MergeFrom(const BinExport2_Expression& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.Expression)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x0000001fu) {
			if (cached_has_bits & 0x00000001u) {
				_internal_set_symbol(from._internal_symbol());
			}
			if (cached_has_bits & 0x00000002u) {
				immediate_ = from.immediate_;
			}
			if (cached_has_bits & 0x00000004u) {
				parent_index_ = from.parent_index_;
			}
			if (cached_has_bits & 0x00000008u) {
				is_relocation_ = from.is_relocation_;
			}
			if (cached_has_bits & 0x00000010u) {
				type_ = from.type_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_Expression::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.Expression)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_Expression::CopyFrom(const BinExport2_Expression& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.Expression)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_Expression::IsInitialized() const {
		return true;
	}

	void BinExport2_Expression::InternalSwap(BinExport2_Expression* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		symbol_.Swap(&other->symbol_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_Expression, is_relocation_)
			+ sizeof(BinExport2_Expression::is_relocation_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_Expression, immediate_)>(
				reinterpret_cast<char*>(&immediate_),
				reinterpret_cast<char*>(&other->immediate_));
		swap(type_, other->type_);
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_Expression::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_Operand::_Internal {
	public:
	};

	BinExport2_Operand::BinExport2_Operand(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena),
		expression_index_(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.Operand)
	}
	BinExport2_Operand::BinExport2_Operand(const BinExport2_Operand& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		expression_index_(from.expression_index_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		// @@protoc_insertion_point(copy_constructor:BinExport2.Operand)
	}

	void BinExport2_Operand::SharedCtor() {
	}

	BinExport2_Operand::~BinExport2_Operand() {
		// @@protoc_insertion_point(destructor:BinExport2.Operand)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_Operand::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_Operand::ArenaDtor(void* object) {
		BinExport2_Operand* _this = reinterpret_cast< BinExport2_Operand* >(object);
		(void)_this;
	}
	void BinExport2_Operand::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_Operand::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_Operand& BinExport2_Operand::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_Operand_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_Operand::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.Operand)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		expression_index_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_Operand::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// repeated int32 expression_index = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					ptr -= 1;
					do {
						ptr += 1;
						_internal_add_expression_index(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<8>(ptr));
				}
				else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10) {
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_expression_index(), ptr, ctx);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_Operand::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.Operand)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		// repeated int32 expression_index = 1;
		for (int i = 0, n = this->_internal_expression_index_size(); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_expression_index(i), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.Operand)
		return target;
	}

	size_t BinExport2_Operand::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.Operand)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		// repeated int32 expression_index = 1;
		{
			size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				Int32Size(this->expression_index_);
			total_size += 1 *
				::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->_internal_expression_index_size());
			total_size += data_size;
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_Operand::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.Operand)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_Operand* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_Operand>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.Operand)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.Operand)
			MergeFrom(*source);
		}
	}

	void BinExport2_Operand::MergeFrom(const BinExport2_Operand& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.Operand)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		expression_index_.MergeFrom(from.expression_index_);
	}

	void BinExport2_Operand::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.Operand)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_Operand::CopyFrom(const BinExport2_Operand& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.Operand)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_Operand::IsInitialized() const {
		return true;
	}

	void BinExport2_Operand::InternalSwap(BinExport2_Operand* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		expression_index_.InternalSwap(&other->expression_index_);
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_Operand::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_Mnemonic::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_Mnemonic>()._has_bits_);
		static void set_has_name(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
	};

	BinExport2_Mnemonic::BinExport2_Mnemonic(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.Mnemonic)
	}
	BinExport2_Mnemonic::BinExport2_Mnemonic(const BinExport2_Mnemonic& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		if (from._internal_has_name()) {
			name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_name(),
				GetArena());
		}
		// @@protoc_insertion_point(copy_constructor:BinExport2.Mnemonic)
	}

	void BinExport2_Mnemonic::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_Mnemonic_binexport2_2eproto.base);
		name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
	}

	BinExport2_Mnemonic::~BinExport2_Mnemonic() {
		// @@protoc_insertion_point(destructor:BinExport2.Mnemonic)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_Mnemonic::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
		name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
	}

	void BinExport2_Mnemonic::ArenaDtor(void* object) {
		BinExport2_Mnemonic* _this = reinterpret_cast< BinExport2_Mnemonic* >(object);
		(void)_this;
	}
	void BinExport2_Mnemonic::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_Mnemonic::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_Mnemonic& BinExport2_Mnemonic::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_Mnemonic_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_Mnemonic::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.Mnemonic)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000001u) {
			name_.ClearNonDefaultToEmpty();
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_Mnemonic::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional string name = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
					auto str = _internal_mutable_name();
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
#ifndef NDEBUG
					::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "BinExport2.Mnemonic.name");
#endif  // !NDEBUG
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_Mnemonic::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.Mnemonic)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional string name = 1;
		if (cached_has_bits & 0x00000001u) {
			::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
				this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
				::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
				"BinExport2.Mnemonic.name");
			target = stream->WriteStringMaybeAliased(
				1, this->_internal_name(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.Mnemonic)
		return target;
	}

	size_t BinExport2_Mnemonic::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.Mnemonic)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		// optional string name = 1;
		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000001u) {
			total_size += 1 +
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
					this->_internal_name());
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_Mnemonic::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.Mnemonic)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_Mnemonic* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_Mnemonic>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.Mnemonic)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.Mnemonic)
			MergeFrom(*source);
		}
	}

	void BinExport2_Mnemonic::MergeFrom(const BinExport2_Mnemonic& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.Mnemonic)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		if (from._internal_has_name()) {
			_internal_set_name(from._internal_name());
		}
	}

	void BinExport2_Mnemonic::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.Mnemonic)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_Mnemonic::CopyFrom(const BinExport2_Mnemonic& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.Mnemonic)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_Mnemonic::IsInitialized() const {
		return true;
	}

	void BinExport2_Mnemonic::InternalSwap(BinExport2_Mnemonic* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		name_.Swap(&other->name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_Mnemonic::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_Instruction::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_Instruction>()._has_bits_);
		static void set_has_address(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
		static void set_has_mnemonic_index(HasBits* has_bits) {
			(*has_bits)[0] |= 4u;
		}
		static void set_has_raw_bytes(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
	};

	BinExport2_Instruction::BinExport2_Instruction(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena),
		call_target_(arena),
		operand_index_(arena),
		comment_index_(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.Instruction)
	}
	BinExport2_Instruction::BinExport2_Instruction(const BinExport2_Instruction& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_),
		call_target_(from.call_target_),
		operand_index_(from.operand_index_),
		comment_index_(from.comment_index_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		raw_bytes_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		if (from._internal_has_raw_bytes()) {
			raw_bytes_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_raw_bytes(),
				GetArena());
		}
		::memcpy(&address_, &from.address_,
			static_cast<size_t>(reinterpret_cast<char*>(&mnemonic_index_) -
				reinterpret_cast<char*>(&address_)) + sizeof(mnemonic_index_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.Instruction)
	}

	void BinExport2_Instruction::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_Instruction_binexport2_2eproto.base);
		raw_bytes_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&address_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&mnemonic_index_) -
				reinterpret_cast<char*>(&address_)) + sizeof(mnemonic_index_));
	}

	BinExport2_Instruction::~BinExport2_Instruction() {
		// @@protoc_insertion_point(destructor:BinExport2.Instruction)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_Instruction::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
		raw_bytes_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
	}

	void BinExport2_Instruction::ArenaDtor(void* object) {
		BinExport2_Instruction* _this = reinterpret_cast< BinExport2_Instruction* >(object);
		(void)_this;
	}
	void BinExport2_Instruction::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_Instruction::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_Instruction& BinExport2_Instruction::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_Instruction_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_Instruction::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.Instruction)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		call_target_.Clear();
		operand_index_.Clear();
		comment_index_.Clear();
		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000001u) {
			raw_bytes_.ClearNonDefaultToEmpty();
		}
		if (cached_has_bits & 0x00000006u) {
			::memset(&address_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&mnemonic_index_) -
				reinterpret_cast<char*>(&address_)) + sizeof(mnemonic_index_));
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_Instruction::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional uint64 address = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					_Internal::set_has_address(&has_bits);
					address_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// repeated uint64 call_target = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
					ptr -= 1;
					do {
						ptr += 1;
						_internal_add_call_target(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<16>(ptr));
				}
				else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18) {
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedUInt64Parser(_internal_mutable_call_target(), ptr, ctx);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 mnemonic_index = 3 [default = 0];
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
					_Internal::set_has_mnemonic_index(&has_bits);
					mnemonic_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// repeated int32 operand_index = 4;
			case 4:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
					ptr -= 1;
					do {
						ptr += 1;
						_internal_add_operand_index(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<32>(ptr));
				}
				else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34) {
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_operand_index(), ptr, ctx);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional bytes raw_bytes = 5;
			case 5:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
					auto str = _internal_mutable_raw_bytes();
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// repeated int32 comment_index = 6;
			case 6:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 48)) {
					ptr -= 1;
					do {
						ptr += 1;
						_internal_add_comment_index(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<48>(ptr));
				}
				else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 50) {
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_comment_index(), ptr, ctx);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_Instruction::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.Instruction)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional uint64 address = 1;
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_address(), target);
		}

		// repeated uint64 call_target = 2;
		for (int i = 0, n = this->_internal_call_target_size(); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(2, this->_internal_call_target(i), target);
		}

		// optional int32 mnemonic_index = 3 [default = 0];
		if (cached_has_bits & 0x00000004u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_mnemonic_index(), target);
		}

		// repeated int32 operand_index = 4;
		for (int i = 0, n = this->_internal_operand_index_size(); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(4, this->_internal_operand_index(i), target);
		}

		// optional bytes raw_bytes = 5;
		if (cached_has_bits & 0x00000001u) {
			target = stream->WriteBytesMaybeAliased(
				5, this->_internal_raw_bytes(), target);
		}

		// repeated int32 comment_index = 6;
		for (int i = 0, n = this->_internal_comment_index_size(); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(6, this->_internal_comment_index(i), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.Instruction)
		return target;
	}

	size_t BinExport2_Instruction::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.Instruction)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		// repeated uint64 call_target = 2;
		{
			size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				UInt64Size(this->call_target_);
			total_size += 1 *
				::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->_internal_call_target_size());
			total_size += data_size;
		}

		// repeated int32 operand_index = 4;
		{
			size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				Int32Size(this->operand_index_);
			total_size += 1 *
				::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->_internal_operand_index_size());
			total_size += data_size;
		}

		// repeated int32 comment_index = 6;
		{
			size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				Int32Size(this->comment_index_);
			total_size += 1 *
				::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->_internal_comment_index_size());
			total_size += data_size;
		}

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000007u) {
			// optional bytes raw_bytes = 5;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
						this->_internal_raw_bytes());
			}

			// optional uint64 address = 1;
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
						this->_internal_address());
			}

			// optional int32 mnemonic_index = 3 [default = 0];
			if (cached_has_bits & 0x00000004u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_mnemonic_index());
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_Instruction::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.Instruction)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_Instruction* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_Instruction>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.Instruction)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.Instruction)
			MergeFrom(*source);
		}
	}

	void BinExport2_Instruction::MergeFrom(const BinExport2_Instruction& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.Instruction)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		call_target_.MergeFrom(from.call_target_);
		operand_index_.MergeFrom(from.operand_index_);
		comment_index_.MergeFrom(from.comment_index_);
		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x00000007u) {
			if (cached_has_bits & 0x00000001u) {
				_internal_set_raw_bytes(from._internal_raw_bytes());
			}
			if (cached_has_bits & 0x00000002u) {
				address_ = from.address_;
			}
			if (cached_has_bits & 0x00000004u) {
				mnemonic_index_ = from.mnemonic_index_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_Instruction::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.Instruction)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_Instruction::CopyFrom(const BinExport2_Instruction& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.Instruction)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_Instruction::IsInitialized() const {
		return true;
	}

	void BinExport2_Instruction::InternalSwap(BinExport2_Instruction* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		call_target_.InternalSwap(&other->call_target_);
		operand_index_.InternalSwap(&other->operand_index_);
		comment_index_.InternalSwap(&other->comment_index_);
		raw_bytes_.Swap(&other->raw_bytes_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_Instruction, mnemonic_index_)
			+ sizeof(BinExport2_Instruction::mnemonic_index_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_Instruction, address_)>(
				reinterpret_cast<char*>(&address_),
				reinterpret_cast<char*>(&other->address_));
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_Instruction::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_BasicBlock_IndexRange::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_BasicBlock_IndexRange>()._has_bits_);
		static void set_has_begin_index(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
		static void set_has_end_index(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
	};

	BinExport2_BasicBlock_IndexRange::BinExport2_BasicBlock_IndexRange(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.BasicBlock.IndexRange)
	}
	BinExport2_BasicBlock_IndexRange::BinExport2_BasicBlock_IndexRange(const BinExport2_BasicBlock_IndexRange& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::memcpy(&begin_index_, &from.begin_index_,
			static_cast<size_t>(reinterpret_cast<char*>(&end_index_) -
				reinterpret_cast<char*>(&begin_index_)) + sizeof(end_index_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.BasicBlock.IndexRange)
	}

	void BinExport2_BasicBlock_IndexRange::SharedCtor() {
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&begin_index_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&end_index_) -
				reinterpret_cast<char*>(&begin_index_)) + sizeof(end_index_));
	}

	BinExport2_BasicBlock_IndexRange::~BinExport2_BasicBlock_IndexRange() {
		// @@protoc_insertion_point(destructor:BinExport2.BasicBlock.IndexRange)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_BasicBlock_IndexRange::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_BasicBlock_IndexRange::ArenaDtor(void* object) {
		BinExport2_BasicBlock_IndexRange* _this = reinterpret_cast< BinExport2_BasicBlock_IndexRange* >(object);
		(void)_this;
	}
	void BinExport2_BasicBlock_IndexRange::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_BasicBlock_IndexRange::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_BasicBlock_IndexRange& BinExport2_BasicBlock_IndexRange::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_BasicBlock_IndexRange_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_BasicBlock_IndexRange::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.BasicBlock.IndexRange)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			::memset(&begin_index_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&end_index_) -
				reinterpret_cast<char*>(&begin_index_)) + sizeof(end_index_));
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_BasicBlock_IndexRange::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional int32 begin_index = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					_Internal::set_has_begin_index(&has_bits);
					begin_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 end_index = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
					_Internal::set_has_end_index(&has_bits);
					end_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_BasicBlock_IndexRange::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.BasicBlock.IndexRange)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional int32 begin_index = 1;
		if (cached_has_bits & 0x00000001u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_begin_index(), target);
		}

		// optional int32 end_index = 2;
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_end_index(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.BasicBlock.IndexRange)
		return target;
	}

	size_t BinExport2_BasicBlock_IndexRange::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.BasicBlock.IndexRange)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			// optional int32 begin_index = 1;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_begin_index());
			}

			// optional int32 end_index = 2;
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_end_index());
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_BasicBlock_IndexRange::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.BasicBlock.IndexRange)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_BasicBlock_IndexRange* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_BasicBlock_IndexRange>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.BasicBlock.IndexRange)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.BasicBlock.IndexRange)
			MergeFrom(*source);
		}
	}

	void BinExport2_BasicBlock_IndexRange::MergeFrom(const BinExport2_BasicBlock_IndexRange& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.BasicBlock.IndexRange)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			if (cached_has_bits & 0x00000001u) {
				begin_index_ = from.begin_index_;
			}
			if (cached_has_bits & 0x00000002u) {
				end_index_ = from.end_index_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_BasicBlock_IndexRange::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.BasicBlock.IndexRange)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_BasicBlock_IndexRange::CopyFrom(const BinExport2_BasicBlock_IndexRange& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.BasicBlock.IndexRange)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_BasicBlock_IndexRange::IsInitialized() const {
		return true;
	}

	void BinExport2_BasicBlock_IndexRange::InternalSwap(BinExport2_BasicBlock_IndexRange* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_BasicBlock_IndexRange, end_index_)
			+ sizeof(BinExport2_BasicBlock_IndexRange::end_index_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_BasicBlock_IndexRange, begin_index_)>(
				reinterpret_cast<char*>(&begin_index_),
				reinterpret_cast<char*>(&other->begin_index_));
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_BasicBlock_IndexRange::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_BasicBlock::_Internal {
	public:
	};

	BinExport2_BasicBlock::BinExport2_BasicBlock(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena),
		instruction_index_(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.BasicBlock)
	}
	BinExport2_BasicBlock::BinExport2_BasicBlock(const BinExport2_BasicBlock& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		instruction_index_(from.instruction_index_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		// @@protoc_insertion_point(copy_constructor:BinExport2.BasicBlock)
	}

	void BinExport2_BasicBlock::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_BasicBlock_binexport2_2eproto.base);
	}

	BinExport2_BasicBlock::~BinExport2_BasicBlock() {
		// @@protoc_insertion_point(destructor:BinExport2.BasicBlock)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_BasicBlock::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_BasicBlock::ArenaDtor(void* object) {
		BinExport2_BasicBlock* _this = reinterpret_cast< BinExport2_BasicBlock* >(object);
		(void)_this;
	}
	void BinExport2_BasicBlock::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_BasicBlock::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_BasicBlock& BinExport2_BasicBlock::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_BasicBlock_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_BasicBlock::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.BasicBlock)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		instruction_index_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_BasicBlock::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// repeated .BinExport2.BasicBlock.IndexRange instruction_index = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_instruction_index(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_BasicBlock::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.BasicBlock)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		// repeated .BinExport2.BasicBlock.IndexRange instruction_index = 1;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_instruction_index_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(1, this->_internal_instruction_index(i), target, stream);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.BasicBlock)
		return target;
	}

	size_t BinExport2_BasicBlock::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.BasicBlock)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		// repeated .BinExport2.BasicBlock.IndexRange instruction_index = 1;
		total_size += 1UL * this->_internal_instruction_index_size();
		for (const auto& msg : this->instruction_index_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_BasicBlock::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.BasicBlock)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_BasicBlock* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_BasicBlock>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.BasicBlock)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.BasicBlock)
			MergeFrom(*source);
		}
	}

	void BinExport2_BasicBlock::MergeFrom(const BinExport2_BasicBlock& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.BasicBlock)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		instruction_index_.MergeFrom(from.instruction_index_);
	}

	void BinExport2_BasicBlock::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.BasicBlock)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_BasicBlock::CopyFrom(const BinExport2_BasicBlock& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.BasicBlock)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_BasicBlock::IsInitialized() const {
		return true;
	}

	void BinExport2_BasicBlock::InternalSwap(BinExport2_BasicBlock* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		instruction_index_.InternalSwap(&other->instruction_index_);
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_BasicBlock::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_FlowGraph_Edge::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_FlowGraph_Edge>()._has_bits_);
		static void set_has_source_basic_block_index(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
		static void set_has_target_basic_block_index(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
		static void set_has_type(HasBits* has_bits) {
			(*has_bits)[0] |= 8u;
		}
		static void set_has_is_back_edge(HasBits* has_bits) {
			(*has_bits)[0] |= 4u;
		}
	};

	BinExport2_FlowGraph_Edge::BinExport2_FlowGraph_Edge(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.FlowGraph.Edge)
	}
	BinExport2_FlowGraph_Edge::BinExport2_FlowGraph_Edge(const BinExport2_FlowGraph_Edge& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::memcpy(&source_basic_block_index_, &from.source_basic_block_index_,
			static_cast<size_t>(reinterpret_cast<char*>(&type_) -
				reinterpret_cast<char*>(&source_basic_block_index_)) + sizeof(type_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.FlowGraph.Edge)
	}

	void BinExport2_FlowGraph_Edge::SharedCtor() {
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&source_basic_block_index_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&is_back_edge_) -
				reinterpret_cast<char*>(&source_basic_block_index_)) + sizeof(is_back_edge_));
		type_ = 3;
	}

	BinExport2_FlowGraph_Edge::~BinExport2_FlowGraph_Edge() {
		// @@protoc_insertion_point(destructor:BinExport2.FlowGraph.Edge)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_FlowGraph_Edge::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_FlowGraph_Edge::ArenaDtor(void* object) {
		BinExport2_FlowGraph_Edge* _this = reinterpret_cast< BinExport2_FlowGraph_Edge* >(object);
		(void)_this;
	}
	void BinExport2_FlowGraph_Edge::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_FlowGraph_Edge::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_FlowGraph_Edge& BinExport2_FlowGraph_Edge::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_FlowGraph_Edge_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_FlowGraph_Edge::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.FlowGraph.Edge)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000000fu) {
			::memset(&source_basic_block_index_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&is_back_edge_) -
				reinterpret_cast<char*>(&source_basic_block_index_)) + sizeof(is_back_edge_));
			type_ = 3;
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_FlowGraph_Edge::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional int32 source_basic_block_index = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					_Internal::set_has_source_basic_block_index(&has_bits);
					source_basic_block_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 target_basic_block_index = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
					_Internal::set_has_target_basic_block_index(&has_bits);
					target_basic_block_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional .BinExport2.FlowGraph.Edge.Type type = 3 [default = UNCONDITIONAL];
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
					::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
					if (PROTOBUF_PREDICT_TRUE(::BinExport2_FlowGraph_Edge_Type_IsValid(val))) {
						_internal_set_type(static_cast<::BinExport2_FlowGraph_Edge_Type>(val));
					}
					else {
						::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(3, val, mutable_unknown_fields());
					}
				}
				else goto handle_unusual;
				continue;
				// optional bool is_back_edge = 4 [default = false];
			case 4:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
					_Internal::set_has_is_back_edge(&has_bits);
					is_back_edge_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_FlowGraph_Edge::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.FlowGraph.Edge)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional int32 source_basic_block_index = 1;
		if (cached_has_bits & 0x00000001u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_source_basic_block_index(), target);
		}

		// optional int32 target_basic_block_index = 2;
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_target_basic_block_index(), target);
		}

		// optional .BinExport2.FlowGraph.Edge.Type type = 3 [default = UNCONDITIONAL];
		if (cached_has_bits & 0x00000008u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
				3, this->_internal_type(), target);
		}

		// optional bool is_back_edge = 4 [default = false];
		if (cached_has_bits & 0x00000004u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(4, this->_internal_is_back_edge(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.FlowGraph.Edge)
		return target;
	}

	size_t BinExport2_FlowGraph_Edge::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.FlowGraph.Edge)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000000fu) {
			// optional int32 source_basic_block_index = 1;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_source_basic_block_index());
			}

			// optional int32 target_basic_block_index = 2;
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_target_basic_block_index());
			}

			// optional bool is_back_edge = 4 [default = false];
			if (cached_has_bits & 0x00000004u) {
				total_size += 1 + 1;
			}

			// optional .BinExport2.FlowGraph.Edge.Type type = 3 [default = UNCONDITIONAL];
			if (cached_has_bits & 0x00000008u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_FlowGraph_Edge::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.FlowGraph.Edge)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_FlowGraph_Edge* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_FlowGraph_Edge>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.FlowGraph.Edge)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.FlowGraph.Edge)
			MergeFrom(*source);
		}
	}

	void BinExport2_FlowGraph_Edge::MergeFrom(const BinExport2_FlowGraph_Edge& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.FlowGraph.Edge)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x0000000fu) {
			if (cached_has_bits & 0x00000001u) {
				source_basic_block_index_ = from.source_basic_block_index_;
			}
			if (cached_has_bits & 0x00000002u) {
				target_basic_block_index_ = from.target_basic_block_index_;
			}
			if (cached_has_bits & 0x00000004u) {
				is_back_edge_ = from.is_back_edge_;
			}
			if (cached_has_bits & 0x00000008u) {
				type_ = from.type_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_FlowGraph_Edge::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.FlowGraph.Edge)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_FlowGraph_Edge::CopyFrom(const BinExport2_FlowGraph_Edge& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.FlowGraph.Edge)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_FlowGraph_Edge::IsInitialized() const {
		return true;
	}

	void BinExport2_FlowGraph_Edge::InternalSwap(BinExport2_FlowGraph_Edge* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_FlowGraph_Edge, is_back_edge_)
			+ sizeof(BinExport2_FlowGraph_Edge::is_back_edge_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_FlowGraph_Edge, source_basic_block_index_)>(
				reinterpret_cast<char*>(&source_basic_block_index_),
				reinterpret_cast<char*>(&other->source_basic_block_index_));
		swap(type_, other->type_);
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_FlowGraph_Edge::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_FlowGraph::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_FlowGraph>()._has_bits_);
		static void set_has_entry_basic_block_index(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
	};

	BinExport2_FlowGraph::BinExport2_FlowGraph(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena),
		basic_block_index_(arena),
		edge_(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.FlowGraph)
	}
	BinExport2_FlowGraph::BinExport2_FlowGraph(const BinExport2_FlowGraph& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_),
		basic_block_index_(from.basic_block_index_),
		edge_(from.edge_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		entry_basic_block_index_ = from.entry_basic_block_index_;
		// @@protoc_insertion_point(copy_constructor:BinExport2.FlowGraph)
	}

	void BinExport2_FlowGraph::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_FlowGraph_binexport2_2eproto.base);
		entry_basic_block_index_ = 0;
	}

	BinExport2_FlowGraph::~BinExport2_FlowGraph() {
		// @@protoc_insertion_point(destructor:BinExport2.FlowGraph)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_FlowGraph::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_FlowGraph::ArenaDtor(void* object) {
		BinExport2_FlowGraph* _this = reinterpret_cast< BinExport2_FlowGraph* >(object);
		(void)_this;
	}
	void BinExport2_FlowGraph::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_FlowGraph::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_FlowGraph& BinExport2_FlowGraph::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_FlowGraph_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_FlowGraph::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.FlowGraph)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		basic_block_index_.Clear();
		edge_.Clear();
		entry_basic_block_index_ = 0;
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_FlowGraph::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// repeated int32 basic_block_index = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					ptr -= 1;
					do {
						ptr += 1;
						_internal_add_basic_block_index(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr));
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<8>(ptr));
				}
				else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10) {
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedInt32Parser(_internal_mutable_basic_block_index(), ptr, ctx);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.FlowGraph.Edge edge = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_edge(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
				}
				else goto handle_unusual;
				continue;
				// optional int32 entry_basic_block_index = 3;
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
					_Internal::set_has_entry_basic_block_index(&has_bits);
					entry_basic_block_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_FlowGraph::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.FlowGraph)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		// repeated int32 basic_block_index = 1;
		for (int i = 0, n = this->_internal_basic_block_index_size(); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_basic_block_index(i), target);
		}

		// repeated .BinExport2.FlowGraph.Edge edge = 2;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_edge_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(2, this->_internal_edge(i), target, stream);
		}

		cached_has_bits = _has_bits_[0];
		// optional int32 entry_basic_block_index = 3;
		if (cached_has_bits & 0x00000001u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_entry_basic_block_index(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.FlowGraph)
		return target;
	}

	size_t BinExport2_FlowGraph::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.FlowGraph)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		// repeated int32 basic_block_index = 1;
		{
			size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				Int32Size(this->basic_block_index_);
			total_size += 1 *
				::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->_internal_basic_block_index_size());
			total_size += data_size;
		}

		// repeated .BinExport2.FlowGraph.Edge edge = 2;
		total_size += 1UL * this->_internal_edge_size();
		for (const auto& msg : this->edge_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// optional int32 entry_basic_block_index = 3;
		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000001u) {
			total_size += 1 +
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
					this->_internal_entry_basic_block_index());
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_FlowGraph::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.FlowGraph)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_FlowGraph* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_FlowGraph>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.FlowGraph)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.FlowGraph)
			MergeFrom(*source);
		}
	}

	void BinExport2_FlowGraph::MergeFrom(const BinExport2_FlowGraph& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.FlowGraph)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		basic_block_index_.MergeFrom(from.basic_block_index_);
		edge_.MergeFrom(from.edge_);
		if (from._internal_has_entry_basic_block_index()) {
			_internal_set_entry_basic_block_index(from._internal_entry_basic_block_index());
		}
	}

	void BinExport2_FlowGraph::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.FlowGraph)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_FlowGraph::CopyFrom(const BinExport2_FlowGraph& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.FlowGraph)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_FlowGraph::IsInitialized() const {
		return true;
	}

	void BinExport2_FlowGraph::InternalSwap(BinExport2_FlowGraph* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		basic_block_index_.InternalSwap(&other->basic_block_index_);
		edge_.InternalSwap(&other->edge_);
		swap(entry_basic_block_index_, other->entry_basic_block_index_);
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_FlowGraph::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_Reference::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_Reference>()._has_bits_);
		static void set_has_instruction_index(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
		static void set_has_instruction_operand_index(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
		static void set_has_operand_expression_index(HasBits* has_bits) {
			(*has_bits)[0] |= 4u;
		}
		static void set_has_string_table_index(HasBits* has_bits) {
			(*has_bits)[0] |= 8u;
		}
	};

	BinExport2_Reference::BinExport2_Reference(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.Reference)
	}
	BinExport2_Reference::BinExport2_Reference(const BinExport2_Reference& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::memcpy(&instruction_index_, &from.instruction_index_,
			static_cast<size_t>(reinterpret_cast<char*>(&string_table_index_) -
				reinterpret_cast<char*>(&instruction_index_)) + sizeof(string_table_index_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.Reference)
	}

	void BinExport2_Reference::SharedCtor() {
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&instruction_index_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&string_table_index_) -
				reinterpret_cast<char*>(&instruction_index_)) + sizeof(string_table_index_));
	}

	BinExport2_Reference::~BinExport2_Reference() {
		// @@protoc_insertion_point(destructor:BinExport2.Reference)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_Reference::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_Reference::ArenaDtor(void* object) {
		BinExport2_Reference* _this = reinterpret_cast< BinExport2_Reference* >(object);
		(void)_this;
	}
	void BinExport2_Reference::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_Reference::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_Reference& BinExport2_Reference::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_Reference_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_Reference::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.Reference)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000000fu) {
			::memset(&instruction_index_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&string_table_index_) -
				reinterpret_cast<char*>(&instruction_index_)) + sizeof(string_table_index_));
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_Reference::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional int32 instruction_index = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					_Internal::set_has_instruction_index(&has_bits);
					instruction_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 instruction_operand_index = 2 [default = 0];
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
					_Internal::set_has_instruction_operand_index(&has_bits);
					instruction_operand_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 operand_expression_index = 3 [default = 0];
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
					_Internal::set_has_operand_expression_index(&has_bits);
					operand_expression_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 string_table_index = 4;
			case 4:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
					_Internal::set_has_string_table_index(&has_bits);
					string_table_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_Reference::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.Reference)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional int32 instruction_index = 1;
		if (cached_has_bits & 0x00000001u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_instruction_index(), target);
		}

		// optional int32 instruction_operand_index = 2 [default = 0];
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_instruction_operand_index(), target);
		}

		// optional int32 operand_expression_index = 3 [default = 0];
		if (cached_has_bits & 0x00000004u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_operand_expression_index(), target);
		}

		// optional int32 string_table_index = 4;
		if (cached_has_bits & 0x00000008u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(4, this->_internal_string_table_index(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.Reference)
		return target;
	}

	size_t BinExport2_Reference::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.Reference)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000000fu) {
			// optional int32 instruction_index = 1;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_instruction_index());
			}

			// optional int32 instruction_operand_index = 2 [default = 0];
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_instruction_operand_index());
			}

			// optional int32 operand_expression_index = 3 [default = 0];
			if (cached_has_bits & 0x00000004u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_operand_expression_index());
			}

			// optional int32 string_table_index = 4;
			if (cached_has_bits & 0x00000008u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_string_table_index());
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_Reference::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.Reference)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_Reference* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_Reference>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.Reference)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.Reference)
			MergeFrom(*source);
		}
	}

	void BinExport2_Reference::MergeFrom(const BinExport2_Reference& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.Reference)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x0000000fu) {
			if (cached_has_bits & 0x00000001u) {
				instruction_index_ = from.instruction_index_;
			}
			if (cached_has_bits & 0x00000002u) {
				instruction_operand_index_ = from.instruction_operand_index_;
			}
			if (cached_has_bits & 0x00000004u) {
				operand_expression_index_ = from.operand_expression_index_;
			}
			if (cached_has_bits & 0x00000008u) {
				string_table_index_ = from.string_table_index_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_Reference::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.Reference)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_Reference::CopyFrom(const BinExport2_Reference& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.Reference)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_Reference::IsInitialized() const {
		return true;
	}

	void BinExport2_Reference::InternalSwap(BinExport2_Reference* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_Reference, string_table_index_)
			+ sizeof(BinExport2_Reference::string_table_index_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_Reference, instruction_index_)>(
				reinterpret_cast<char*>(&instruction_index_),
				reinterpret_cast<char*>(&other->instruction_index_));
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_Reference::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_DataReference::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_DataReference>()._has_bits_);
		static void set_has_instruction_index(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
		static void set_has_address(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
	};

	BinExport2_DataReference::BinExport2_DataReference(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.DataReference)
	}
	BinExport2_DataReference::BinExport2_DataReference(const BinExport2_DataReference& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::memcpy(&address_, &from.address_,
			static_cast<size_t>(reinterpret_cast<char*>(&instruction_index_) -
				reinterpret_cast<char*>(&address_)) + sizeof(instruction_index_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.DataReference)
	}

	void BinExport2_DataReference::SharedCtor() {
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&address_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&instruction_index_) -
				reinterpret_cast<char*>(&address_)) + sizeof(instruction_index_));
	}

	BinExport2_DataReference::~BinExport2_DataReference() {
		// @@protoc_insertion_point(destructor:BinExport2.DataReference)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_DataReference::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_DataReference::ArenaDtor(void* object) {
		BinExport2_DataReference* _this = reinterpret_cast< BinExport2_DataReference* >(object);
		(void)_this;
	}
	void BinExport2_DataReference::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_DataReference::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_DataReference& BinExport2_DataReference::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_DataReference_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_DataReference::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.DataReference)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			::memset(&address_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&instruction_index_) -
				reinterpret_cast<char*>(&address_)) + sizeof(instruction_index_));
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_DataReference::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional int32 instruction_index = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					_Internal::set_has_instruction_index(&has_bits);
					instruction_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional uint64 address = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
					_Internal::set_has_address(&has_bits);
					address_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_DataReference::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.DataReference)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional int32 instruction_index = 1;
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_instruction_index(), target);
		}

		// optional uint64 address = 2;
		if (cached_has_bits & 0x00000001u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(2, this->_internal_address(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.DataReference)
		return target;
	}

	size_t BinExport2_DataReference::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.DataReference)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			// optional uint64 address = 2;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
						this->_internal_address());
			}

			// optional int32 instruction_index = 1;
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_instruction_index());
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_DataReference::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.DataReference)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_DataReference* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_DataReference>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.DataReference)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.DataReference)
			MergeFrom(*source);
		}
	}

	void BinExport2_DataReference::MergeFrom(const BinExport2_DataReference& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.DataReference)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			if (cached_has_bits & 0x00000001u) {
				address_ = from.address_;
			}
			if (cached_has_bits & 0x00000002u) {
				instruction_index_ = from.instruction_index_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_DataReference::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.DataReference)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_DataReference::CopyFrom(const BinExport2_DataReference& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.DataReference)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_DataReference::IsInitialized() const {
		return true;
	}

	void BinExport2_DataReference::InternalSwap(BinExport2_DataReference* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_DataReference, instruction_index_)
			+ sizeof(BinExport2_DataReference::instruction_index_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_DataReference, address_)>(
				reinterpret_cast<char*>(&address_),
				reinterpret_cast<char*>(&other->address_));
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_DataReference::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_Comment::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_Comment>()._has_bits_);
		static void set_has_instruction_index(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
		static void set_has_instruction_operand_index(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
		static void set_has_operand_expression_index(HasBits* has_bits) {
			(*has_bits)[0] |= 4u;
		}
		static void set_has_string_table_index(HasBits* has_bits) {
			(*has_bits)[0] |= 8u;
		}
		static void set_has_repeatable(HasBits* has_bits) {
			(*has_bits)[0] |= 16u;
		}
		static void set_has_type(HasBits* has_bits) {
			(*has_bits)[0] |= 32u;
		}
	};

	BinExport2_Comment::BinExport2_Comment(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.Comment)
	}
	BinExport2_Comment::BinExport2_Comment(const BinExport2_Comment& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::memcpy(&instruction_index_, &from.instruction_index_,
			static_cast<size_t>(reinterpret_cast<char*>(&type_) -
				reinterpret_cast<char*>(&instruction_index_)) + sizeof(type_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.Comment)
	}

	void BinExport2_Comment::SharedCtor() {
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&instruction_index_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&type_) -
				reinterpret_cast<char*>(&instruction_index_)) + sizeof(type_));
	}

	BinExport2_Comment::~BinExport2_Comment() {
		// @@protoc_insertion_point(destructor:BinExport2.Comment)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_Comment::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_Comment::ArenaDtor(void* object) {
		BinExport2_Comment* _this = reinterpret_cast< BinExport2_Comment* >(object);
		(void)_this;
	}
	void BinExport2_Comment::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_Comment::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_Comment& BinExport2_Comment::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_Comment_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_Comment::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.Comment)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000003fu) {
			::memset(&instruction_index_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&type_) -
				reinterpret_cast<char*>(&instruction_index_)) + sizeof(type_));
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_Comment::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional int32 instruction_index = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					_Internal::set_has_instruction_index(&has_bits);
					instruction_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 instruction_operand_index = 2 [default = 0];
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
					_Internal::set_has_instruction_operand_index(&has_bits);
					instruction_operand_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 operand_expression_index = 3 [default = 0];
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
					_Internal::set_has_operand_expression_index(&has_bits);
					operand_expression_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional int32 string_table_index = 4;
			case 4:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
					_Internal::set_has_string_table_index(&has_bits);
					string_table_index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional bool repeatable = 5;
			case 5:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
					_Internal::set_has_repeatable(&has_bits);
					repeatable_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional .BinExport2.Comment.Type type = 6 [default = DEFAULT];
			case 6:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 48)) {
					::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
					if (PROTOBUF_PREDICT_TRUE(::BinExport2_Comment_Type_IsValid(val))) {
						_internal_set_type(static_cast<::BinExport2_Comment_Type>(val));
					}
					else {
						::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(6, val, mutable_unknown_fields());
					}
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_Comment::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.Comment)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional int32 instruction_index = 1;
		if (cached_has_bits & 0x00000001u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_instruction_index(), target);
		}

		// optional int32 instruction_operand_index = 2 [default = 0];
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_instruction_operand_index(), target);
		}

		// optional int32 operand_expression_index = 3 [default = 0];
		if (cached_has_bits & 0x00000004u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_operand_expression_index(), target);
		}

		// optional int32 string_table_index = 4;
		if (cached_has_bits & 0x00000008u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(4, this->_internal_string_table_index(), target);
		}

		// optional bool repeatable = 5;
		if (cached_has_bits & 0x00000010u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(5, this->_internal_repeatable(), target);
		}

		// optional .BinExport2.Comment.Type type = 6 [default = DEFAULT];
		if (cached_has_bits & 0x00000020u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
				6, this->_internal_type(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.Comment)
		return target;
	}

	size_t BinExport2_Comment::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.Comment)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000003fu) {
			// optional int32 instruction_index = 1;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_instruction_index());
			}

			// optional int32 instruction_operand_index = 2 [default = 0];
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_instruction_operand_index());
			}

			// optional int32 operand_expression_index = 3 [default = 0];
			if (cached_has_bits & 0x00000004u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_operand_expression_index());
			}

			// optional int32 string_table_index = 4;
			if (cached_has_bits & 0x00000008u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
						this->_internal_string_table_index());
			}

			// optional bool repeatable = 5;
			if (cached_has_bits & 0x00000010u) {
				total_size += 1 + 1;
			}

			// optional .BinExport2.Comment.Type type = 6 [default = DEFAULT];
			if (cached_has_bits & 0x00000020u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_Comment::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.Comment)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_Comment* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_Comment>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.Comment)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.Comment)
			MergeFrom(*source);
		}
	}

	void BinExport2_Comment::MergeFrom(const BinExport2_Comment& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.Comment)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x0000003fu) {
			if (cached_has_bits & 0x00000001u) {
				instruction_index_ = from.instruction_index_;
			}
			if (cached_has_bits & 0x00000002u) {
				instruction_operand_index_ = from.instruction_operand_index_;
			}
			if (cached_has_bits & 0x00000004u) {
				operand_expression_index_ = from.operand_expression_index_;
			}
			if (cached_has_bits & 0x00000008u) {
				string_table_index_ = from.string_table_index_;
			}
			if (cached_has_bits & 0x00000010u) {
				repeatable_ = from.repeatable_;
			}
			if (cached_has_bits & 0x00000020u) {
				type_ = from.type_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_Comment::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.Comment)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_Comment::CopyFrom(const BinExport2_Comment& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.Comment)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_Comment::IsInitialized() const {
		return true;
	}

	void BinExport2_Comment::InternalSwap(BinExport2_Comment* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_Comment, type_)
			+ sizeof(BinExport2_Comment::type_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_Comment, instruction_index_)>(
				reinterpret_cast<char*>(&instruction_index_),
				reinterpret_cast<char*>(&other->instruction_index_));
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_Comment::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_Section::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_Section>()._has_bits_);
		static void set_has_address(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
		static void set_has_size(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
		static void set_has_flag_r(HasBits* has_bits) {
			(*has_bits)[0] |= 4u;
		}
		static void set_has_flag_w(HasBits* has_bits) {
			(*has_bits)[0] |= 8u;
		}
		static void set_has_flag_x(HasBits* has_bits) {
			(*has_bits)[0] |= 16u;
		}
	};

	BinExport2_Section::BinExport2_Section(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.Section)
	}
	BinExport2_Section::BinExport2_Section(const BinExport2_Section& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::memcpy(&address_, &from.address_,
			static_cast<size_t>(reinterpret_cast<char*>(&flag_x_) -
				reinterpret_cast<char*>(&address_)) + sizeof(flag_x_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.Section)
	}

	void BinExport2_Section::SharedCtor() {
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&address_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&flag_x_) -
				reinterpret_cast<char*>(&address_)) + sizeof(flag_x_));
	}

	BinExport2_Section::~BinExport2_Section() {
		// @@protoc_insertion_point(destructor:BinExport2.Section)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_Section::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
	}

	void BinExport2_Section::ArenaDtor(void* object) {
		BinExport2_Section* _this = reinterpret_cast< BinExport2_Section* >(object);
		(void)_this;
	}
	void BinExport2_Section::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_Section::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_Section& BinExport2_Section::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_Section_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_Section::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.Section)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000001fu) {
			::memset(&address_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&flag_x_) -
				reinterpret_cast<char*>(&address_)) + sizeof(flag_x_));
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_Section::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional uint64 address = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					_Internal::set_has_address(&has_bits);
					address_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional uint64 size = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
					_Internal::set_has_size(&has_bits);
					size_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional bool flag_r = 3;
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
					_Internal::set_has_flag_r(&has_bits);
					flag_r_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional bool flag_w = 4;
			case 4:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
					_Internal::set_has_flag_w(&has_bits);
					flag_w_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional bool flag_x = 5;
			case 5:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
					_Internal::set_has_flag_x(&has_bits);
					flag_x_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_Section::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.Section)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional uint64 address = 1;
		if (cached_has_bits & 0x00000001u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_address(), target);
		}

		// optional uint64 size = 2;
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(2, this->_internal_size(), target);
		}

		// optional bool flag_r = 3;
		if (cached_has_bits & 0x00000004u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(3, this->_internal_flag_r(), target);
		}

		// optional bool flag_w = 4;
		if (cached_has_bits & 0x00000008u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(4, this->_internal_flag_w(), target);
		}

		// optional bool flag_x = 5;
		if (cached_has_bits & 0x00000010u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(5, this->_internal_flag_x(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.Section)
		return target;
	}

	size_t BinExport2_Section::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.Section)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x0000001fu) {
			// optional uint64 address = 1;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
						this->_internal_address());
			}

			// optional uint64 size = 2;
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
						this->_internal_size());
			}

			// optional bool flag_r = 3;
			if (cached_has_bits & 0x00000004u) {
				total_size += 1 + 1;
			}

			// optional bool flag_w = 4;
			if (cached_has_bits & 0x00000008u) {
				total_size += 1 + 1;
			}

			// optional bool flag_x = 5;
			if (cached_has_bits & 0x00000010u) {
				total_size += 1 + 1;
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_Section::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.Section)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_Section* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_Section>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.Section)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.Section)
			MergeFrom(*source);
		}
	}

	void BinExport2_Section::MergeFrom(const BinExport2_Section& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.Section)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x0000001fu) {
			if (cached_has_bits & 0x00000001u) {
				address_ = from.address_;
			}
			if (cached_has_bits & 0x00000002u) {
				size_ = from.size_;
			}
			if (cached_has_bits & 0x00000004u) {
				flag_r_ = from.flag_r_;
			}
			if (cached_has_bits & 0x00000008u) {
				flag_w_ = from.flag_w_;
			}
			if (cached_has_bits & 0x00000010u) {
				flag_x_ = from.flag_x_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_Section::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.Section)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_Section::CopyFrom(const BinExport2_Section& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.Section)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_Section::IsInitialized() const {
		return true;
	}

	void BinExport2_Section::InternalSwap(BinExport2_Section* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_Section, flag_x_)
			+ sizeof(BinExport2_Section::flag_x_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_Section, address_)>(
				reinterpret_cast<char*>(&address_),
				reinterpret_cast<char*>(&other->address_));
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_Section::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_Library::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_Library>()._has_bits_);
		static void set_has_is_static(HasBits* has_bits) {
			(*has_bits)[0] |= 4u;
		}
		static void set_has_load_address(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
		static void set_has_name(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
	};

	BinExport2_Library::BinExport2_Library(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.Library)
	}
	BinExport2_Library::BinExport2_Library(const BinExport2_Library& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		if (from._internal_has_name()) {
			name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_name(),
				GetArena());
		}
		::memcpy(&load_address_, &from.load_address_,
			static_cast<size_t>(reinterpret_cast<char*>(&is_static_) -
				reinterpret_cast<char*>(&load_address_)) + sizeof(is_static_));
		// @@protoc_insertion_point(copy_constructor:BinExport2.Library)
	}

	void BinExport2_Library::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_Library_binexport2_2eproto.base);
		name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&load_address_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&is_static_) -
				reinterpret_cast<char*>(&load_address_)) + sizeof(is_static_));
	}

	BinExport2_Library::~BinExport2_Library() {
		// @@protoc_insertion_point(destructor:BinExport2.Library)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_Library::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
		name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
	}

	void BinExport2_Library::ArenaDtor(void* object) {
		BinExport2_Library* _this = reinterpret_cast< BinExport2_Library* >(object);
		(void)_this;
	}
	void BinExport2_Library::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_Library::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_Library& BinExport2_Library::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_Library_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_Library::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.Library)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000001u) {
			name_.ClearNonDefaultToEmpty();
		}
		if (cached_has_bits & 0x00000006u) {
			::memset(&load_address_, 0, static_cast<size_t>(
				reinterpret_cast<char*>(&is_static_) -
				reinterpret_cast<char*>(&load_address_)) + sizeof(is_static_));
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_Library::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional bool is_static = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
					_Internal::set_has_is_static(&has_bits);
					is_static_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional uint64 load_address = 2 [default = 0];
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
					_Internal::set_has_load_address(&has_bits);
					load_address_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// optional string name = 3;
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
					auto str = _internal_mutable_name();
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
#ifndef NDEBUG
					::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "BinExport2.Library.name");
#endif  // !NDEBUG
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_Library::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.Library)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional bool is_static = 1;
		if (cached_has_bits & 0x00000004u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(1, this->_internal_is_static(), target);
		}

		// optional uint64 load_address = 2 [default = 0];
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(2, this->_internal_load_address(), target);
		}

		// optional string name = 3;
		if (cached_has_bits & 0x00000001u) {
			::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
				this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
				::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
				"BinExport2.Library.name");
			target = stream->WriteStringMaybeAliased(
				3, this->_internal_name(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.Library)
		return target;
	}

	size_t BinExport2_Library::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.Library)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000007u) {
			// optional string name = 3;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
						this->_internal_name());
			}

			// optional uint64 load_address = 2 [default = 0];
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
						this->_internal_load_address());
			}

			// optional bool is_static = 1;
			if (cached_has_bits & 0x00000004u) {
				total_size += 1 + 1;
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_Library::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.Library)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_Library* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_Library>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.Library)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.Library)
			MergeFrom(*source);
		}
	}

	void BinExport2_Library::MergeFrom(const BinExport2_Library& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.Library)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x00000007u) {
			if (cached_has_bits & 0x00000001u) {
				_internal_set_name(from._internal_name());
			}
			if (cached_has_bits & 0x00000002u) {
				load_address_ = from.load_address_;
			}
			if (cached_has_bits & 0x00000004u) {
				is_static_ = from.is_static_;
			}
			_has_bits_[0] |= cached_has_bits;
		}
	}

	void BinExport2_Library::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.Library)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_Library::CopyFrom(const BinExport2_Library& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.Library)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_Library::IsInitialized() const {
		return true;
	}

	void BinExport2_Library::InternalSwap(BinExport2_Library* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		name_.Swap(&other->name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2_Library, is_static_)
			+ sizeof(BinExport2_Library::is_static_)
			- PROTOBUF_FIELD_OFFSET(BinExport2_Library, load_address_)>(
				reinterpret_cast<char*>(&load_address_),
				reinterpret_cast<char*>(&other->load_address_));
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_Library::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2_Module::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2_Module>()._has_bits_);
		static void set_has_name(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
	};

	BinExport2_Module::BinExport2_Module(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2.Module)
	}
	BinExport2_Module::BinExport2_Module(const BinExport2_Module& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
		if (from._internal_has_name()) {
			name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_name(),
				GetArena());
		}
		// @@protoc_insertion_point(copy_constructor:BinExport2.Module)
	}

	void BinExport2_Module::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_Module_binexport2_2eproto.base);
		name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
	}

	BinExport2_Module::~BinExport2_Module() {
		// @@protoc_insertion_point(destructor:BinExport2.Module)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2_Module::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
		name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
	}

	void BinExport2_Module::ArenaDtor(void* object) {
		BinExport2_Module* _this = reinterpret_cast< BinExport2_Module* >(object);
		(void)_this;
	}
	void BinExport2_Module::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2_Module::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2_Module& BinExport2_Module::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_Module_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2_Module::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2.Module)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000001u) {
			name_.ClearNonDefaultToEmpty();
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2_Module::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional string name = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
					auto str = _internal_mutable_name();
					ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
#ifndef NDEBUG
					::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "BinExport2.Module.name");
#endif  // !NDEBUG
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2_Module::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2.Module)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional string name = 1;
		if (cached_has_bits & 0x00000001u) {
			::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
				this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
				::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
				"BinExport2.Module.name");
			target = stream->WriteStringMaybeAliased(
				1, this->_internal_name(), target);
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2.Module)
		return target;
	}

	size_t BinExport2_Module::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2.Module)
		size_t total_size = 0;

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		// optional string name = 1;
		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000001u) {
			total_size += 1 +
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
					this->_internal_name());
		}

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2_Module::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2.Module)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2_Module* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2_Module>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2.Module)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2.Module)
			MergeFrom(*source);
		}
	}

	void BinExport2_Module::MergeFrom(const BinExport2_Module& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2.Module)
		GOOGLE_DCHECK_NE(&from, this);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		if (from._internal_has_name()) {
			_internal_set_name(from._internal_name());
		}
	}

	void BinExport2_Module::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2.Module)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2_Module::CopyFrom(const BinExport2_Module& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2.Module)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2_Module::IsInitialized() const {
		return true;
	}

	void BinExport2_Module::InternalSwap(BinExport2_Module* other) {
		using std::swap;
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		name_.Swap(&other->name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2_Module::GetMetadata() const {
		return GetMetadataStatic();
	}


	// ===================================================================

	class BinExport2::_Internal {
	public:
		using HasBits = decltype(std::declval<BinExport2>()._has_bits_);
		static const ::BinExport2_Meta& meta_information(const BinExport2* msg);
		static void set_has_meta_information(HasBits* has_bits) {
			(*has_bits)[0] |= 1u;
		}
		static const ::BinExport2_CallGraph& call_graph(const BinExport2* msg);
		static void set_has_call_graph(HasBits* has_bits) {
			(*has_bits)[0] |= 2u;
		}
	};

	const ::BinExport2_Meta&
		BinExport2::_Internal::meta_information(const BinExport2* msg) {
		return *msg->meta_information_;
	}
	const ::BinExport2_CallGraph&
		BinExport2::_Internal::call_graph(const BinExport2* msg) {
		return *msg->call_graph_;
	}
	BinExport2::BinExport2(::PROTOBUF_NAMESPACE_ID::Arena* arena)
		: ::PROTOBUF_NAMESPACE_ID::Message(arena),
		_extensions_(arena),
		expression_(arena),
		operand_(arena),
		mnemonic_(arena),
		instruction_(arena),
		basic_block_(arena),
		flow_graph_(arena),
		string_table_(arena),
		address_comment_(arena),
		string_reference_(arena),
		expression_substitution_(arena),
		section_(arena),
		library_(arena),
		data_reference_(arena),
		module_(arena),
		comment_(arena) {
		SharedCtor();
		RegisterArenaDtor(arena);
		// @@protoc_insertion_point(arena_constructor:BinExport2)
	}
	BinExport2::BinExport2(const BinExport2& from)
		: ::PROTOBUF_NAMESPACE_ID::Message(),
		_has_bits_(from._has_bits_),
		expression_(from.expression_),
		operand_(from.operand_),
		mnemonic_(from.mnemonic_),
		instruction_(from.instruction_),
		basic_block_(from.basic_block_),
		flow_graph_(from.flow_graph_),
		string_table_(from.string_table_),
		address_comment_(from.address_comment_),
		string_reference_(from.string_reference_),
		expression_substitution_(from.expression_substitution_),
		section_(from.section_),
		library_(from.library_),
		data_reference_(from.data_reference_),
		module_(from.module_),
		comment_(from.comment_) {
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		_extensions_.MergeFrom(from._extensions_);
		if (from._internal_has_meta_information()) {
			meta_information_ = new ::BinExport2_Meta(*from.meta_information_);
		}
		else {
			meta_information_ = nullptr;
		}
		if (from._internal_has_call_graph()) {
			call_graph_ = new ::BinExport2_CallGraph(*from.call_graph_);
		}
		else {
			call_graph_ = nullptr;
		}
		// @@protoc_insertion_point(copy_constructor:BinExport2)
	}

	void BinExport2::SharedCtor() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_BinExport2_binexport2_2eproto.base);
		::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
			reinterpret_cast<char*>(&meta_information_) - reinterpret_cast<char*>(this)),
			0, static_cast<size_t>(reinterpret_cast<char*>(&call_graph_) -
				reinterpret_cast<char*>(&meta_information_)) + sizeof(call_graph_));
	}

	BinExport2::~BinExport2() {
		// @@protoc_insertion_point(destructor:BinExport2)
		SharedDtor();
		_internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	void BinExport2::SharedDtor() {
		GOOGLE_DCHECK(GetArena() == nullptr);
		if (this != internal_default_instance()) delete meta_information_;
		if (this != internal_default_instance()) delete call_graph_;
	}

	void BinExport2::ArenaDtor(void* object) {
		BinExport2* _this = reinterpret_cast< BinExport2* >(object);
		(void)_this;
	}
	void BinExport2::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
	}
	void BinExport2::SetCachedSize(int size) const {
		_cached_size_.Set(size);
	}
	const BinExport2& BinExport2::default_instance() {
		::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_BinExport2_binexport2_2eproto.base);
		return *internal_default_instance();
	}


	void BinExport2::Clear() {
		// @@protoc_insertion_point(message_clear_start:BinExport2)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		_extensions_.Clear();
		expression_.Clear();
		operand_.Clear();
		mnemonic_.Clear();
		instruction_.Clear();
		basic_block_.Clear();
		flow_graph_.Clear();
		string_table_.Clear();
		address_comment_.Clear();
		string_reference_.Clear();
		expression_substitution_.Clear();
		section_.Clear();
		library_.Clear();
		data_reference_.Clear();
		module_.Clear();
		comment_.Clear();
		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			if (cached_has_bits & 0x00000001u) {
				GOOGLE_DCHECK(meta_information_ != nullptr);
				meta_information_->Clear();
			}
			if (cached_has_bits & 0x00000002u) {
				GOOGLE_DCHECK(call_graph_ != nullptr);
				call_graph_->Clear();
			}
		}
		_has_bits_.Clear();
		_internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
	}

	const char* BinExport2::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
		_Internal::HasBits has_bits{};
		while (!ctx->Done(&ptr)) {
			::PROTOBUF_NAMESPACE_ID::uint32 tag;
			ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
			CHK_(ptr);
			switch (tag >> 3) {
				// optional .BinExport2.Meta meta_information = 1;
			case 1:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
					ptr = ctx->ParseMessage(_internal_mutable_meta_information(), ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Expression expression = 2;
			case 2:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_expression(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Operand operand = 3;
			case 3:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_operand(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<26>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Mnemonic mnemonic = 4;
			case 4:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_mnemonic(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<34>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Instruction instruction = 5;
			case 5:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_instruction(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<42>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.BasicBlock basic_block = 6;
			case 6:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 50)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_basic_block(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<50>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.FlowGraph flow_graph = 7;
			case 7:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 58)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_flow_graph(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<58>(ptr));
				}
				else goto handle_unusual;
				continue;
				// optional .BinExport2.CallGraph call_graph = 8;
			case 8:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 66)) {
					ptr = ctx->ParseMessage(_internal_mutable_call_graph(), ptr);
					CHK_(ptr);
				}
				else goto handle_unusual;
				continue;
				// repeated string string_table = 9;
			case 9:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 74)) {
					ptr -= 1;
					do {
						ptr += 1;
						auto str = _internal_add_string_table();
						ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
#ifndef NDEBUG
						::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "BinExport2.string_table");
#endif  // !NDEBUG
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<74>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Reference address_comment = 10 [deprecated = true];
			case 10:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 82)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_address_comment(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<82>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Reference string_reference = 11;
			case 11:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 90)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_string_reference(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<90>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Reference expression_substitution = 12;
			case 12:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 98)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_expression_substitution(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<98>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Section section = 13;
			case 13:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 106)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_section(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<106>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Library library = 14;
			case 14:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 114)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_library(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<114>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.DataReference data_reference = 15;
			case 15:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 122)) {
					ptr -= 1;
					do {
						ptr += 1;
						ptr = ctx->ParseMessage(_internal_add_data_reference(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<122>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Module module = 16;
			case 16:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 130)) {
					ptr -= 2;
					do {
						ptr += 2;
						ptr = ctx->ParseMessage(_internal_add_module(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<130>(ptr));
				}
				else goto handle_unusual;
				continue;
				// repeated .BinExport2.Comment comment = 17;
			case 17:
				if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 138)) {
					ptr -= 2;
					do {
						ptr += 2;
						ptr = ctx->ParseMessage(_internal_add_comment(), ptr);
						CHK_(ptr);
						if (!ctx->DataAvailable(ptr)) break;
					} while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<138>(ptr));
				}
				else goto handle_unusual;
				continue;
			default: {
			handle_unusual:
				if ((tag & 7) == 4 || tag == 0) {
					ctx->SetLastTag(tag);
					goto success;
				}
				if ((800000000u <= tag)) {
					ptr = _extensions_.ParseField(tag, ptr,
						internal_default_instance(), &_internal_metadata_, ctx);
					CHK_(ptr != nullptr);
					continue;
				}
				ptr = UnknownFieldParse(tag,
					_internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
					ptr, ctx);
				CHK_(ptr != nullptr);
				continue;
			}
			}  // switch
		}  // while
	success:
		_has_bits_.Or(has_bits);
		return ptr;
	failure:
		ptr = nullptr;
		goto success;
#undef CHK_
	}

	::PROTOBUF_NAMESPACE_ID::uint8* BinExport2::_InternalSerialize(
		::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
		// @@protoc_insertion_point(serialize_to_array_start:BinExport2)
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		cached_has_bits = _has_bits_[0];
		// optional .BinExport2.Meta meta_information = 1;
		if (cached_has_bits & 0x00000001u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(
					1, _Internal::meta_information(this), target, stream);
		}

		// repeated .BinExport2.Expression expression = 2;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_expression_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(2, this->_internal_expression(i), target, stream);
		}

		// repeated .BinExport2.Operand operand = 3;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_operand_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(3, this->_internal_operand(i), target, stream);
		}

		// repeated .BinExport2.Mnemonic mnemonic = 4;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_mnemonic_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(4, this->_internal_mnemonic(i), target, stream);
		}

		// repeated .BinExport2.Instruction instruction = 5;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_instruction_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(5, this->_internal_instruction(i), target, stream);
		}

		// repeated .BinExport2.BasicBlock basic_block = 6;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_basic_block_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(6, this->_internal_basic_block(i), target, stream);
		}

		// repeated .BinExport2.FlowGraph flow_graph = 7;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_flow_graph_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(7, this->_internal_flow_graph(i), target, stream);
		}

		// optional .BinExport2.CallGraph call_graph = 8;
		if (cached_has_bits & 0x00000002u) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(
					8, _Internal::call_graph(this), target, stream);
		}

		// repeated string string_table = 9;
		for (int i = 0, n = this->_internal_string_table_size(); i < n; i++) {
			const auto& s = this->_internal_string_table(i);
			::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
				s.data(), static_cast<int>(s.length()),
				::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
				"BinExport2.string_table");
			target = stream->WriteString(9, s, target);
		}

		// repeated .BinExport2.Reference address_comment = 10 [deprecated = true];
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_address_comment_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(10, this->_internal_address_comment(i), target, stream);
		}

		// repeated .BinExport2.Reference string_reference = 11;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_string_reference_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(11, this->_internal_string_reference(i), target, stream);
		}

		// repeated .BinExport2.Reference expression_substitution = 12;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_expression_substitution_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(12, this->_internal_expression_substitution(i), target, stream);
		}

		// repeated .BinExport2.Section section = 13;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_section_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(13, this->_internal_section(i), target, stream);
		}

		// repeated .BinExport2.Library library = 14;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_library_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(14, this->_internal_library(i), target, stream);
		}

		// repeated .BinExport2.DataReference data_reference = 15;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_data_reference_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(15, this->_internal_data_reference(i), target, stream);
		}

		// repeated .BinExport2.Module module = 16;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_module_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(16, this->_internal_module(i), target, stream);
		}

		// repeated .BinExport2.Comment comment = 17;
		for (unsigned int i = 0,
			n = static_cast<unsigned int>(this->_internal_comment_size()); i < n; i++) {
			target = stream->EnsureSpace(target);
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
				InternalWriteMessage(17, this->_internal_comment(i), target, stream);
		}

		// Extension range [100000000, 536870912)
		target = _extensions_._InternalSerialize(
			100000000, 536870912, target, stream);

		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
				_internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
		}
		// @@protoc_insertion_point(serialize_to_array_end:BinExport2)
		return target;
	}

	size_t BinExport2::ByteSizeLong() const {
		// @@protoc_insertion_point(message_byte_size_start:BinExport2)
		size_t total_size = 0;

		total_size += _extensions_.ByteSize();

		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		// Prevent compiler warnings about cached_has_bits being unused
		(void)cached_has_bits;

		// repeated .BinExport2.Expression expression = 2;
		total_size += 1UL * this->_internal_expression_size();
		for (const auto& msg : this->expression_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.Operand operand = 3;
		total_size += 1UL * this->_internal_operand_size();
		for (const auto& msg : this->operand_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.Mnemonic mnemonic = 4;
		total_size += 1UL * this->_internal_mnemonic_size();
		for (const auto& msg : this->mnemonic_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.Instruction instruction = 5;
		total_size += 1UL * this->_internal_instruction_size();
		for (const auto& msg : this->instruction_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.BasicBlock basic_block = 6;
		total_size += 1UL * this->_internal_basic_block_size();
		for (const auto& msg : this->basic_block_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.FlowGraph flow_graph = 7;
		total_size += 1UL * this->_internal_flow_graph_size();
		for (const auto& msg : this->flow_graph_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated string string_table = 9;
		total_size += 1 *
			::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(string_table_.size());
		for (int i = 0, n = string_table_.size(); i < n; i++) {
			total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
				string_table_.Get(i));
		}

		// repeated .BinExport2.Reference address_comment = 10 [deprecated = true];
		total_size += 1UL * this->_internal_address_comment_size();
		for (const auto& msg : this->address_comment_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.Reference string_reference = 11;
		total_size += 1UL * this->_internal_string_reference_size();
		for (const auto& msg : this->string_reference_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.Reference expression_substitution = 12;
		total_size += 1UL * this->_internal_expression_substitution_size();
		for (const auto& msg : this->expression_substitution_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.Section section = 13;
		total_size += 1UL * this->_internal_section_size();
		for (const auto& msg : this->section_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.Library library = 14;
		total_size += 1UL * this->_internal_library_size();
		for (const auto& msg : this->library_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.DataReference data_reference = 15;
		total_size += 1UL * this->_internal_data_reference_size();
		for (const auto& msg : this->data_reference_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.Module module = 16;
		total_size += 2UL * this->_internal_module_size();
		for (const auto& msg : this->module_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		// repeated .BinExport2.Comment comment = 17;
		total_size += 2UL * this->_internal_comment_size();
		for (const auto& msg : this->comment_) {
			total_size +=
				::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
		}

		cached_has_bits = _has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			// optional .BinExport2.Meta meta_information = 1;
			if (cached_has_bits & 0x00000001u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
						*meta_information_);
			}

			// optional .BinExport2.CallGraph call_graph = 8;
			if (cached_has_bits & 0x00000002u) {
				total_size += 1 +
					::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
						*call_graph_);
			}

		}
		if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
			return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
				_internal_metadata_, total_size, &_cached_size_);
		}
		int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
		SetCachedSize(cached_size);
		return total_size;
	}

	void BinExport2::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_merge_from_start:BinExport2)
		GOOGLE_DCHECK_NE(&from, this);
		const BinExport2* source =
			::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<BinExport2>(
				&from);
		if (source == nullptr) {
			// @@protoc_insertion_point(generalized_merge_from_cast_fail:BinExport2)
			::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
		}
		else {
			// @@protoc_insertion_point(generalized_merge_from_cast_success:BinExport2)
			MergeFrom(*source);
		}
	}

	void BinExport2::MergeFrom(const BinExport2& from) {
		// @@protoc_insertion_point(class_specific_merge_from_start:BinExport2)
		GOOGLE_DCHECK_NE(&from, this);
		_extensions_.MergeFrom(from._extensions_);
		_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
		::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
		(void)cached_has_bits;

		expression_.MergeFrom(from.expression_);
		operand_.MergeFrom(from.operand_);
		mnemonic_.MergeFrom(from.mnemonic_);
		instruction_.MergeFrom(from.instruction_);
		basic_block_.MergeFrom(from.basic_block_);
		flow_graph_.MergeFrom(from.flow_graph_);
		string_table_.MergeFrom(from.string_table_);
		address_comment_.MergeFrom(from.address_comment_);
		string_reference_.MergeFrom(from.string_reference_);
		expression_substitution_.MergeFrom(from.expression_substitution_);
		section_.MergeFrom(from.section_);
		library_.MergeFrom(from.library_);
		data_reference_.MergeFrom(from.data_reference_);
		module_.MergeFrom(from.module_);
		comment_.MergeFrom(from.comment_);
		cached_has_bits = from._has_bits_[0];
		if (cached_has_bits & 0x00000003u) {
			if (cached_has_bits & 0x00000001u) {
				_internal_mutable_meta_information()->::BinExport2_Meta::MergeFrom(from._internal_meta_information());
			}
			if (cached_has_bits & 0x00000002u) {
				_internal_mutable_call_graph()->::BinExport2_CallGraph::MergeFrom(from._internal_call_graph());
			}
		}
	}

	void BinExport2::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
		// @@protoc_insertion_point(generalized_copy_from_start:BinExport2)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	void BinExport2::CopyFrom(const BinExport2& from) {
		// @@protoc_insertion_point(class_specific_copy_from_start:BinExport2)
		if (&from == this) return;
		Clear();
		MergeFrom(from);
	}

	bool BinExport2::IsInitialized() const {
		if (!_extensions_.IsInitialized()) {
			return false;
		}

		return true;
	}

	void BinExport2::InternalSwap(BinExport2* other) {
		using std::swap;
		_extensions_.Swap(&other->_extensions_);
		_internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
		swap(_has_bits_[0], other->_has_bits_[0]);
		expression_.InternalSwap(&other->expression_);
		operand_.InternalSwap(&other->operand_);
		mnemonic_.InternalSwap(&other->mnemonic_);
		instruction_.InternalSwap(&other->instruction_);
		basic_block_.InternalSwap(&other->basic_block_);
		flow_graph_.InternalSwap(&other->flow_graph_);
		string_table_.InternalSwap(&other->string_table_);
		address_comment_.InternalSwap(&other->address_comment_);
		string_reference_.InternalSwap(&other->string_reference_);
		expression_substitution_.InternalSwap(&other->expression_substitution_);
		section_.InternalSwap(&other->section_);
		library_.InternalSwap(&other->library_);
		data_reference_.InternalSwap(&other->data_reference_);
		module_.InternalSwap(&other->module_);
		comment_.InternalSwap(&other->comment_);
		::PROTOBUF_NAMESPACE_ID::internal::memswap<
			PROTOBUF_FIELD_OFFSET(BinExport2, call_graph_)
			+ sizeof(BinExport2::call_graph_)
			- PROTOBUF_FIELD_OFFSET(BinExport2, meta_information_)>(
				reinterpret_cast<char*>(&meta_information_),
				reinterpret_cast<char*>(&other->meta_information_));
	}

	::PROTOBUF_NAMESPACE_ID::Metadata BinExport2::GetMetadata() const {
		return GetMetadataStatic();
	}


	// @@protoc_insertion_point(namespace_scope)
	PROTOBUF_NAMESPACE_OPEN
		template<> PROTOBUF_NOINLINE::BinExport2_Meta* Arena::CreateMaybeMessage< ::BinExport2_Meta >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_Meta >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_CallGraph_Vertex* Arena::CreateMaybeMessage< ::BinExport2_CallGraph_Vertex >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_CallGraph_Vertex >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_CallGraph_Edge* Arena::CreateMaybeMessage< ::BinExport2_CallGraph_Edge >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_CallGraph_Edge >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_CallGraph* Arena::CreateMaybeMessage< ::BinExport2_CallGraph >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_CallGraph >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_Expression* Arena::CreateMaybeMessage< ::BinExport2_Expression >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_Expression >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_Operand* Arena::CreateMaybeMessage< ::BinExport2_Operand >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_Operand >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_Mnemonic* Arena::CreateMaybeMessage< ::BinExport2_Mnemonic >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_Mnemonic >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_Instruction* Arena::CreateMaybeMessage< ::BinExport2_Instruction >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_Instruction >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_BasicBlock_IndexRange* Arena::CreateMaybeMessage< ::BinExport2_BasicBlock_IndexRange >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_BasicBlock_IndexRange >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_BasicBlock* Arena::CreateMaybeMessage< ::BinExport2_BasicBlock >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_BasicBlock >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_FlowGraph_Edge* Arena::CreateMaybeMessage< ::BinExport2_FlowGraph_Edge >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_FlowGraph_Edge >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_FlowGraph* Arena::CreateMaybeMessage< ::BinExport2_FlowGraph >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_FlowGraph >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_Reference* Arena::CreateMaybeMessage< ::BinExport2_Reference >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_Reference >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_DataReference* Arena::CreateMaybeMessage< ::BinExport2_DataReference >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_DataReference >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_Comment* Arena::CreateMaybeMessage< ::BinExport2_Comment >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_Comment >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_Section* Arena::CreateMaybeMessage< ::BinExport2_Section >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_Section >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_Library* Arena::CreateMaybeMessage< ::BinExport2_Library >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_Library >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2_Module* Arena::CreateMaybeMessage< ::BinExport2_Module >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2_Module >(arena);
	}
	template<> PROTOBUF_NOINLINE::BinExport2* Arena::CreateMaybeMessage< ::BinExport2 >(Arena* arena) {
		return Arena::CreateMessageInternal< ::BinExport2 >(arena);
	}
	PROTOBUF_NAMESPACE_CLOSE

		// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
