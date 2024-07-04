#include <tetris_game/highscores.h>
#include <algorithm>
#include <cassert>
#include <fstream>

namespace fs = std::filesystem;

namespace {
void Parse (std::ifstream& source, HighScores::ScoreRecord& target)
{
    source.read (reinterpret_cast <char*> (&target.score), sizeof (target.score));
    source.read (reinterpret_cast <char*> (&target.lines), sizeof (target.lines));
    target.isNew = false;
}
}

bool HighScoresSavReader::Read (fs::path path, HighScores& target)
{
    if (!fs::exists (path)) {
        return false;
    }
    std::ifstream sav;
    sav.open (path.native(), std::ios::in | std::ios_base::binary);
    if (sav.is_open()) {
        size_t elemsNum (0);
        sav.read (reinterpret_cast <char*> (&elemsNum), sizeof (elemsNum));
        while (elemsNum != 0 && elemsNum <= 10) // validity verification
        {
            HighScores::ScoreRecord record;
            Parse (sav, record);
            target.AddSavedScore (std::move (record));
            elemsNum--;
        }
    } else 
        return false;
    sav.close();
    return true;
}

bool HighScoresSavWriter::Write (const HighScores& source, std::filesystem::path folderPath, const std::wstring& filename)
{
    if (!fs::exists (folderPath)) {
        fs::create_directories (folderPath);
    }

    folderPath /= filename;
    std::ofstream sav;
    sav.open (folderPath.native(), std::ios::out | std::ios::binary);
    if (sav.is_open()) {
        auto records = source.GetRecords();
        size_t recordsNum = records.size();
        sav.write (reinterpret_cast <char*> (&recordsNum), sizeof (recordsNum));
        for (auto& record : records) {
            sav.write (reinterpret_cast <char*> (&record.score), sizeof (record.score));
            sav.write (reinterpret_cast <char*> (&record.lines), sizeof (record.lines));
        }
    } else {
        return false;
    }
    sav.close();
    return true;
}

HighScores::HighScores()
{
    m_records.reserve (11);
}

void HighScores::AddNewScore (size_t score, size_t lines)
{
    for (auto& record: m_records) {
        record.isNew = false;
    }
    m_records.emplace_back (score, lines, true);
    std::ranges::sort (m_records, [] (const ScoreRecord& sr1, const ScoreRecord& sr2) { return sr1.score > sr2.score; });
    if (m_records.size() > 10) {
        m_records.pop_back();
    }
}

void HighScores::AddSavedScore (size_t score, size_t lines)
{
    m_records.emplace_back (score, lines, false);
    assert ((void ("Invalid amount of records"), m_records.size() <= 10));
}

void HighScores::AddSavedScore (ScoreRecord&& record)
{
    m_records.push_back (std::move (record));
    assert ((void ("Invalid amount of records"), m_records.size () <= 10));
}

