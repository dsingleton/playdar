#include "demo.h"
#include <boost/algorithm/string.hpp>
#include "playdar/playable_item.hpp"
#include "playdar/resolver_query.hpp"

namespace playdar {
namespace resolvers {

/*
    Called once when plugin is loaded when playdar starts up.
*/
bool
demo::init( pa_ptr pap )
{
    m_pap = pap;
    std::cout << "Demo resolver init(): "
              << "this only finds 'Sweet Melissa' by the artist 'Big Bad Sun'"
              << std::endl;
    return true;
}

/*
    The start_resolving call must not block. Most plugins will have their own
    threading model, and would typically do any slow searching in a new thread.
    
    This example does not use threads, because it just matches a single
    hardcoded track, and is thus very fast.
    
    A ResolverQuery is passed in - this represents the search to execute.
    
    Notice this call returns void - the resolving framework is asynchronous,
    and you can call report_results() at any time after the search was started,
    when a result is found.
*/
void
demo::start_resolving(boost::shared_ptr<ResolverQuery> rq)
{
    //Only resolve if we have an artist and track to resolve against.
    if( !rq->param_exists("artist") || rq->param_type("artist") != json_spirit::str_type || 
        !rq->param_exists("track") || rq->param_type("track") != json_spirit::str_type )
        return;
        
    // we'll only resolve an exact match to one song.
    if( boost::to_lower_copy(rq->param("artist").get_str())  == "big bad sun" &&
        boost::to_lower_copy(rq->param("track").get_str())   == "sweet melissa" )
    {
        // PlayableItems represent results - they hold metadata
        // for the track we resolved the search to, and extra data
        // such as the score (how good a match was it?)
        // the bitrate, filesize, etc.
        boost::shared_ptr<PlayableItem> pip
            (new PlayableItem("Big Bad Sun", 
                              "", // no album name specified
                              "Sweet Melissa"));
                              
        pip->set_score(1.0);    // Exact match, so set maximum score
        pip->set_bitrate(128);  // avg. bitrate in kbps
        pip->set_size(3401187); // filesize
        pip->set_duration(203); // play duration, seconds
        
        // Create streaming strategy for accessing the track:
        pip->set_url( "http://he3.magnatune.com/all/01-Sweet%20Melissa-Big%20Bad%20Sun.mp3" );
        // Results are a list of resolveditems:
        vector< json_spirit::Object> v;
        // .. containing just the one match we found:
        v.push_back(pip->get_json());
        // tell the resolver what we found:
        m_pap->report_results(rq->id(), v);
    }
    else
    {
        // just do nothing.
        // resolvers should only respond if they find a match.
    }
}


} // resolvers
} // playdar
