#include "WorkList.h"
#include "WorkItem.h"

#include <utility>

#include "glslang/glslang/OSDependent/osinclude.h"

namespace NodeGLSLang {

    // TODO this class is to be used once glslang supports multithreaded compilation on all platforms...

    WorkList::WorkList() {
    }


    WorkList::WorkList( std::list<WorkItemPtr>&& work ) : _work( std::move( work ) ) {
    }


    void WorkList::pushBack( const WorkItemPtr& item ) {
        glslang::GetGlobalLock();
        _work.push_back( item );
        glslang::ReleaseGlobalLock();
    }


    bool WorkList::popFront( WorkItemPtr& outItem ) {

        glslang::GetGlobalLock();

        if ( _work.empty() ) {
            return false;
        }

        outItem = _work.front();
        _work.pop_front();

        glslang::ReleaseGlobalLock();

        return true;
    }


    size_t WorkList::size() const {

        size_t size;

        glslang::GetGlobalLock();
        size = _work.size();
        glslang::ReleaseGlobalLock();

        return size;
    }


    bool WorkList::empty() const {

        bool isEmpty;

        glslang::GetGlobalLock();
        isEmpty = _work.empty();
        glslang::ReleaseGlobalLock();

        return isEmpty;
    }

} // namespace
