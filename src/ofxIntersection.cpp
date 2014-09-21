//
//  ofxInersection.cpp
//  emptyExample
//
//  Created by Matthias Rohrbach on 16.09.14.
//
//

#include "ofxIntersection.h"

ofxIntersection::ofxIntersection(){
    
}

/************** Ray  ************/
IntersectionData ofxIntersection::RayPlaneIntersection(Ray&ray, Plane &plane){
    IntersectionData idata;
    float u=0;
    float denom = plane.getNormal().dot(ray.getVec());

    // check if ray is paralles to plane:
    if (denom > EPS) {
        u= plane.getNormal().dot(plane.getP0()-ray.getP0())/denom;
        idata.isIntersection=true;
        idata.pos.set(ray.getP0()+ray.getVec()*u);
        return idata;
    }else{
        idata.isIntersection=false;
        return idata;
    }
    
}

IntersectionData ofxIntersection::RayTriangleIntersection(Triangle& triangle, Ray& ray){
    
}



float ofxIntersection::PointPlaneDistance(ofPoint &point, Plane &plane){
    return  plane.getNormal().dot((point-plane.getP0()));
}



/************** Line  ************/

IntersectionData ofxIntersection::LinePlaneIntersection(Line& line, Plane& plane){
    IntersectionData idata;
   
    if(ofSign(PointPlaneDistance(line.p0, plane))==ofSign(PointPlaneDistance(line.p1, plane))){
        idata.isIntersection=false;
        return idata;
    };
    
    float u=0;
    float denom = plane.getNormal().dot(line.getVec());
    
    // check if ray is paralles to plane:
    if (fabs(denom) > EPS) {
        u= plane.getNormal().dot(plane.getP0()-line.getP0())/denom;
        
        // check if intersection is within line-segment:
        if(u>1.0 || u<0){
            idata.isIntersection=false;
            return idata;
        }
        idata.isIntersection=true;
        idata.pos.set(line.getP0()+line.getVec()*u);
        return idata;
    }else{
        idata.isIntersection=false;
        return idata;
    }
}



IntersectionData ofxIntersection::LineLineIntersection(Line& line1, Line& line2){
    IntersectionData idata;
    
    ofPoint p13,p43,p21;
    ofPoint p1=line1.getP0();
    ofPoint p2=line1.getP1();
    ofPoint p3=line2.getP0();
    ofPoint p4=line2.getP1();
    
    double d1343,d4321,d1321,d4343,d2121;
    double numer,denom;
    double mua, mub;
    ofPoint pa, pb;
    
    p13.x = p1.x - p3.x;
    p13.y = p1.y - p3.y;
    p13.z = p1.z - p3.z;
    p43.x = p4.x - p3.x;
    p43.y = p4.y - p3.y;
    p43.z = p4.z - p3.z;
    if (ABS(p43.x) < EPS && ABS(p43.y) < EPS && ABS(p43.z) < EPS){
        idata.isIntersection=false;
        return idata;
    }
    
    p21.x = p2.x - p1.x;
    p21.y = p2.y - p1.y;
    p21.z = p2.z - p1.z;

    if (ABS(p21.x) < EPS && ABS(p21.y) < EPS && ABS(p21.z) < EPS){
        idata.isIntersection=false;
        return idata;
    }
    
    d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
    d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
    d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
    d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
    d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;
    
    denom = d2121 * d4343 - d4321 * d4321;
    if (ABS(denom) < EPS){
        idata.isIntersection=false;
        return idata;
    }
    
    numer = d1343 * d4321 - d1321 * d4343;
    mua = numer / denom;
    mub = (d1343 + d4321 * (mua)) / d4343;
    
    pa.x = p1.x + mua * p21.x;
    pa.y = p1.y + mua * p21.y;
    pa.z = p1.z + mua * p21.z;
    pb.x = p3.x + mub * p43.x;
    pb.y = p3.y + mub * p43.y;
    pb.z = p3.z + mub * p43.z;
    
    idata.isIntersection=true;
    idata.pos.set(pa);
    idata.dir.set(pb-pa);
    return idata;
    
}


IntersectionData ofxIntersection::PointLineDistance(ofPoint& point, Line& line){
    float u;
    ofVec3f dist;
    IntersectionData idata;
    
    
    u = ( ( ( point.x - line.getP0().x ) * ( line.getVec().x ) +
           ( ( point.y - line.getP0().y ) * ( line.getVec().y) ) +
           ( ( point.z - line.getP0().z ) * ( line.getVec().z) ) ) /
         ( line.getVec().lengthSquared()));
    
    if( u < 0.0f || u > 1.0f ){
        idata.isIntersection=false;
        return idata;
    }
    
    idata.isIntersection=true;
    idata.pos.x = line.getP0().x + u * ( line.getVec().x );
    idata.pos.y = line.getP0().y + u * ( line.getVec().y );
    idata.pos.z = line.getP0().z + u * ( line.getVec().z );
    idata.dir.set(idata.pos- point);
    
    return idata;
    
}





/************** Plane  ************/


IntersectionData ofxIntersection::PlanePlaneIntersection(Plane &plane1, Plane& plane2){
    IntersectionData idata;
    
    
    
    return idata;
}

IntersectionData ofxIntersection::PlaneTriangleIntersection(Plane& plane, Triangle& triangle){
    IntersectionData idata;
    
    Line lines[3];
    lines[0]=triangle.getSeg0();
    lines[1]=triangle.getSeg1();
    lines[2]=triangle.getSeg2();
    
    vector<ofPoint>ispoints;
    IntersectionData id[3];
    bool bintersects=false;
    
    for(int i=0;i<3;i++){
        id[i]=LinePlaneIntersection(lines[i], plane);
        if(id[i].isIntersection){
            bintersects=true;
            if(!containsValue(&ispoints,id[i].pos)){
                ispoints.push_back(id[i].pos);
            };
        }
    }
    
    if(!bintersects){
        idata.isIntersection=false;
        return idata;
    }
    
    
    idata.isIntersection=true;
    idata.pos.set(ispoints.at(0));
    idata.dir.set(0,0,0);
    idata.dist=0;
    
    if(ispoints.size()==2){
        idata.dir.set(ispoints.at(1));
        idata.dir-=idata.pos;
        idata.dist=idata.dir.length();
    }
    return idata;
}


bool ofxIntersection::containsValue(vector<ofPoint> *points, ofPoint point){
    for(int i=0;i<points->size();i++){
        if((points->at(i)-point).length()<EPS ){
            return true;
        }
    }
    return false;
}