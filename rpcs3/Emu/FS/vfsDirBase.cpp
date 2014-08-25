#include "stdafx.h"
#include "vfsDevice.h"
#include "vfsDirBase.h"
#include "Utilities/rFile.h"

vfsDirBase::vfsDirBase(vfsDevice* device)
	: m_pos(0)
	, m_device(device)
{
}

vfsDirBase::~vfsDirBase()
{
}

bool vfsDirBase::Open(const std::string& path)
{
	if(IsOpened())
		Close();

	if(!IsExists(path))
		return false;

	m_pos = 0;
	m_cwd += '/' + path;
	return true;
}

bool vfsDirBase::IsOpened() const
{
	return !m_cwd.empty();
}

bool vfsDirBase::IsExists(const std::string& path) const
{
	return rExists(path);
}

const std::vector<DirEntryInfo>& vfsDirBase::GetEntries() const
{
	return m_entries;
}

void vfsDirBase::Close()
{
	m_cwd = "";
	m_entries.clear();
}

std::string vfsDirBase::GetPath() const
{
	return m_cwd;
}

const DirEntryInfo* vfsDirBase::Read()
{
	if (m_pos >= m_entries.size())
		return nullptr;

	return &m_entries[m_pos++];
}
