#ifndef __PLAYDAR_LIBRARY_H__
#define __PLAYDAR_LIBRARY_H__

#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <boost/thread.hpp>
#include "sqlite3pp.h"

#include "playdar/types.h"
#include "playdar/artist.h"
#include "playdar/album.h"
#include "playdar/track.h"
#include "playdar/library_file.h"


class MyApplication;

class Library
{
public:
    Library(const std::string& dbfilepath);
    ~Library();

    int add_dir( const std::string& url, int mtime);
    int add_file( const std::string& url, int mtime, int size, const std::string& md5, const std::string& mimetype,
                  int duration, int bitrate,
                  const std::string& artist, const std::string& album, const std::string& track, int tracknum);
    
    bool remove_file( const std::string& url );

    int get_artist_id(const std::string&);
    int get_track_id(int, const std::string&);
    int get_album_id(int, const std::string&);

    std::map<std::string, int> file_mtimes();
    int num_files();
    int num_artists();
    int num_albums();
    int num_tracks();

    bool build_index(std::string);
    static std::string sortname(const std::string& name);
    std::map<std::string, int> ngrams(const std::string&);

    std::vector<scorepair> search_catalogue(std::string, std::string);
    std::vector<scorepair> search_catalogue_for_artist(int, std::string, std::string);

    // catalogue items
    artist_ptr  load_artist(std::string n);
    artist_ptr  load_artist(int n);
    
    album_ptr   load_album(artist_ptr artp, std::string n);
    album_ptr   load_album(int n);
    
    track_ptr   load_track(artist_ptr artp, std::string n);
    track_ptr   load_track(int n);

    // browsing:
    std::vector< boost::shared_ptr<Artist> > list_artists();
    std::vector< boost::shared_ptr<Track> > list_artist_tracks(boost::shared_ptr<Artist>);
    
    std::string get_name(std::string, int);
    std::string get_field(std::string, int, std::string);

    std::vector<int> get_fids_for_tid(int tid);
    LibraryFile_ptr file_from_fid(int fid);

    sqlite3pp::database * db() { return &m_db; }
    std::string dbfilepath() const { return m_dbfilepath; }
    
    // DB helper:
    template <typename T> T db_get_one(std::string sql, T def);
    
private:
    sqlite3pp::database m_db;
    boost::mutex m_mut;
    std::string m_dbfilepath;
    // name -> id caches
    std::map< std::string, int > m_artistcache;
    std::map< int, std::map<std::string, int> > m_trackcache;
    std::map< int, std::map<std::string, int> > m_albumcache;
};


#endif

