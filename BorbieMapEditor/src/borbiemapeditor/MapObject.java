package borbiemapeditor;

/**
 *
 * @author richard
 */
// Contains all variables associated with an individual map object such
//  as a building, tree or lamp.
public class MapObject {
    
    // types of objects that this object can be
    public static final int TYPE_BUILDING = 0;
    public static final int TYPE_LAMP = 1;
    public static final int TYPE_TREE = 2;
    public static final int TYPE_FIRE_HYDRANT = 3;
    public static final int TYPE_ROAD_INTERSECTION = 4;
    public static final int TYPE_VEHICLE_SPAWN = 5;
    public static final int TYPE_ENEMY_SPAWN = 6;
    
    // internal object variables: X and Y represent the CENTER
    public int x;
    public int y;
    public int width;
    public int height;
    public boolean selected;
    
    // values used externally for only some types (i.e. road intersections,
    //  spawn points)
    public int id;
    public char sType;
    public int connectedWith;
    
    // type of this specific object
    public int type;
    
    
    // given the objects CENTER X and CENTER Y, and it's actual
    //  width and height
    public MapObject(int x, int y, int width, int height, int type){
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.type = type;
        this.id = 0;
        this.connectedWith = -1;
        this.selected = false;
    }
    
    
    // returns TRUE if the given points intersect this object's square area,
    //  with the fact that this.x and this.y implies the CENTER of the object.
    public boolean intersects(int otherX, int otherY){
        int lowX = this.x - this.width / 2;
        int highX = this.x + this.width / 2;
        int lowY = this.y - this.height / 2;
        int highY = this.y + this.height / 2;
        return (lowX <= otherX && highX >= otherX) &&
               (lowY <= otherY && highY >= otherY);
    }
    
    
    // returns TRUE if the given points resembling a box intersect this object's
    //  square area with the fact that this.x and this.y implies the CENTER.
    // PARAMETERS: Excepts that otherLowX <= otherHighX and otherLowY <= otherHighY
    //  (these are the bounding 2D regions of the selection box)
    public boolean intersects(
            int otherLowX, int otherLowY, int otherHighX, int otherHighY){
        // get bounding regions for this box
        int lowX = this.x - this.width / 2;
        int highX = this.x + this.width / 2;
        int lowY = this.y - this.height / 2;
        int highY = this.y + this.height / 2;
        // return if there is an intersection
        return (lowX <= otherHighX) && (highX >= otherLowX) &&
                (lowY <= otherHighY) && (highY >= otherLowY);
    }
    
    
    // returns a new instance that is an exact copy of this object
    @Override
    public MapObject clone(){
        MapObject newMapObj = new MapObject(
                this.x, this.y, this.width, this.height, this.type);
        newMapObj.selected = this.selected;
        return newMapObj;
    }
    
}
