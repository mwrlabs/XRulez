#pragma once

namespace MapiTools
{
	/// Useful wrapper for IMsgStore structure.
	struct ExchangeModifyTable : public CppTools::PointerObject<ExchangeModifyTable, IExchangeModifyTable>
	{
		/// Move constructor.
		ExchangeModifyTable(ExchangeModifyTable&&) = default;

		/// Destructor.
		~ExchangeModifyTable() { if (!m_Pointer) return; m_Pointer->Release(); m_Pointer = nullptr; }

		/// Opens a MAPI table on the Exchange table property. This table can be read to determine what the Exchange table looks like.
		/// @return Opened MapiTable object.
		MapiTools::MapiTable GetMapiTable();

		/// Deletes a specified rule.
		/// @param ruleId ID of rule to delete.
		/// @return false if rule of provided ID doesn't exist. True if rule was successfully deleted. Other Mapi errors are thrown as MapiException.
		CppTools::XError<bool> DeleteRule(LARGE_INTEGER const& ruleId);

		/// Structure describing a single inbox rule.
		struct RuleInfo
		{
			std::wstring m_Name;												//< Name of the rule.
			std::wstring m_Provider;											//< Provider of the rule.
			LARGE_INTEGER m_Id;													//< Rule's ID.
			ULONG m_SequenceNo;													//< Sequential number.
		};

		/// Enlists all rules in this table.
		/// @return list of rules.
		/// @remarks throws MapiException on MAPI call failures.
		std::vector<RuleInfo> EnumerateRules();

	protected:
		/// Protected ctor.
		ExchangeModifyTable(LPEXCHANGEMODIFYTABLE exchangeModifyTable) : PointerObject(exchangeModifyTable) { ValidateParam(exchangeModifyTable); }

		/// Friendships.
		friend struct MapiFolder;
	};
}
