#pragma once
#include <map>

template<typename T, typename K> class Vertex {
    public: 
		Vertex(T data){
			this->data     = data;
            this->visited  = false;
			this->distance = 0;
			this->parent   = nullptr;			
		}

		/*
		 * This function adds an arc struct going from the Vertex* origin parameter
		 * to the Vertex* dest parameter with a weight of the float price parameter.   
		 */
		bool addArc(Vertex* destination, K weight) {
			if(destination == nullptr)
				return false;

			int prevSize = arcMap.size();
	
			arcMap.insert({destination, weight});	

			if(this->arcMap.size() - prevSize == 1) {
				return true;
			} else {
				return false;
			}
		}

		bool removeArc(Vertex* destination){
			if(destination == nullptr)
				return false;
			
		/*	for(int i = 0; i < prevSize; i++) {
				Arc* arc = this->arcList->get(i);

				if(arc->vertex->data == destination->data) {
					this->arcList->remove(i);
					break;
				}
			}
            */
          // this->arcMap<Vertex*, K>::iterator it = this->arcMap->find(destination);
            auto it = this->arcMap.find(destination);
           if(it != this->arcMap.end()){
                this->arcMap.erase(destination);
                return true;
           } else {
            return false;
           }
		}

		T getData() {
			return this->data;
		}

		std::map<Vertex*, K> get_arc_list() {
			return this->arcMap;
		}

		bool getVisited() {
			return this->visited;
		}

		void setVisited(bool visit) {
			this->visited = visit;
		}

		/*
		 * The get_weight function takes a Vertex* origin vertex that goes to the 
		 * Vertex* destination vertex parameter and returns the weight of that arc 
		 * if such an arc exists. -1 is returned if no such arc exists.
		 */
		K getWeight(Vertex* destination) {
			if(destination == nullptr)
				return -1;

		    /*	
            for(int i = 0; i < this->arcList->getSize(); i++) {
			    	Arc* arc = this->arcList->get(i);
					
				// If the destination vertex is found in this vertex's arc list.	
				// MAY NEED TO COMPARE THE VERTICES AND NOT THE DATA BASED ON MEMORY ADDRESS	
				if(this->data == destination->data) {
					return arc->weight;
				}
			}
            */

           auto it = this->arcMap.find(destination);
           if(it != this->arcMap.end()){
                return this->arcMap[destination];
           } else {
            return -1;
           }
		}

		/*
		 * The change_vertex_weight function takes an origin and destination Vertex* and changes the
		 * weight associated with the arc from the origin vertex to the destination vertex to the
		 * value of the cost parameter. 
		 */
		bool changeWeight(Vertex* destination, K weight) {
			if(destination == nullptr)
				return false;
            /*
			for(int i = 0; i < this->arcList->getSize(); i++) {
				Arc* arc  = this->arcList->get(i);

				// If this arc's vertex is equal to the destination vertex
				// MAY NEED TO COMPARE THE VERTICES AND NOT THE DATA BASED ON MEMORY ADDRESS
				if(destination->data == arc->vertex->data) {
					arc->setWeight(weight);
					return true;
				}
			}
            */

            auto it = this->arcMap.find(destination);
            if(it != this->arcMap.end()){
                this->arcMap[destination] = weight;
                return true;
           } else {
            return false;
           }

		//	return false;
		}

		void setDistance(K distance) {
			this->distance = distance;
		}	

		K getDistance() {
			return this->distance;
		}
			
		bool hasArc(Vertex* v) {
            auto it = this->arcMap.find(v);
            if(it != this->arcMap.end()){
                return true;
           } else {
            return false;
           }
		}

		std::map<Vertex*, K> getArcMap(){
			return this->arcMap;
		}

	private:
		T data;
		bool visited;
		K distance;
		Vertex* parent;
        std::map<Vertex*, K> arcMap;

        void setParent(Vertex* v) {
			this->parent = v;
		}

		Vertex* getParent() {
			return this->parent;
		}
};
