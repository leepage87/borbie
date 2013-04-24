package borbiemapeditor;

import java.awt.Color;
import java.awt.Font;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;
import javax.swing.AbstractButton;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JToggleButton;

/**
 *
 * @author richard
 */
public class MenuPanel extends JPanel {
    
    // selection mode: which button is currently selected
    public static enum MenuSelection {
        POINTER, BUILDING, ROAD_INTERSECTION, ROAD_PATH,
        LAMP, TREE, HYDRANT, ERASE, SELECT
    }
    
    // list of editor buttons
    private final JButton pointerButton;
    private final JButton buildingButton;
    private final JButton roadButton;
    private final JButton roadPathButton;
    private final JButton lampButton;
    private final JButton treeButton;
    private final JButton fireHydrantButton;
    private final JButton eraseButton;
    private final JButton selectButton;
    
    // selection
    private MenuSelection selection = MenuSelection.BUILDING;
    
    
    // CONSTRUCTOR
    public MenuPanel() {
        super();
        
        this.setBackground(Color.PINK);
        this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        
        // button font
        Font buttonFont = new Font(Font.MONOSPACED, Font.BOLD, 14);
        
        // get all icons here
        ImageIcon pointerIcon = getIcon("pointer.png");
        ImageIcon buildingIcon = getIcon("building.png");
        ImageIcon roadIcon = getIcon("intersection.png");
        ImageIcon roadPathIcon = getIcon("road.png");
        ImageIcon lampIcon = getIcon("lamp.png");
        ImageIcon treeIcon = getIcon("tree.png");
        ImageIcon fireHydrantIcon = getIcon("hydrant.png");
        ImageIcon eraseIcon = getIcon("eraser.png");
        ImageIcon selectIcon = getIcon("select.png");
        
        pointerButton = new JButton(" Pointer     ", pointerIcon);
        pointerButton.setVerticalTextPosition(AbstractButton.CENTER);
        pointerButton.setHorizontalTextPosition(AbstractButton.TRAILING);
        pointerButton.setToolTipText("Select and drag map objects.");
        pointerButton.setFont(buttonFont);
        pointerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                selectPointer();
            }
        });
        pointerButton.setEnabled(false);
        pointerButton.setFocusable(false);
        this.add(pointerButton);
        
        // add the button for the building
        buildingButton = new JButton(" Building    ", buildingIcon);
        buildingButton.setVerticalTextPosition(AbstractButton.CENTER);
        buildingButton.setHorizontalTextPosition(AbstractButton.TRAILING);
        buildingButton.setToolTipText("Add a building to the map.");
        buildingButton.setFont(buttonFont);
        buildingButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                selectAddBuilding();
            }
        });
        buildingButton.setEnabled(false);
        buildingButton.setFocusable(false);
        this.add(buildingButton);

        roadButton = new JButton(" Intersection", roadIcon);
        roadButton.setVerticalTextPosition(AbstractButton.CENTER);
        roadButton.setHorizontalTextPosition(AbstractButton.TRAILING);
        roadButton.setToolTipText("Add road intersections to the map.");
        roadButton.setFont(buttonFont);
        roadButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                selectAddRoad();
            }
        });
        roadButton.setEnabled(false);
        roadButton.setFocusable(false);
        this.add(roadButton);

        roadPathButton = new JButton(" Road Path   ", roadPathIcon);
        roadPathButton.setVerticalTextPosition(AbstractButton.CENTER);
        roadPathButton.setHorizontalTextPosition(AbstractButton.TRAILING);
        roadPathButton.setToolTipText("Add road segments to the map.");
        roadPathButton.setFont(buttonFont);
        roadPathButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                selectAddRoadPath();
            }
        });
        roadPathButton.setEnabled(false);
        roadPathButton.setFocusable(false);
        this.add(roadPathButton);
        
        lampButton = new JButton(" Street Lamp ", lampIcon);
        lampButton.setVerticalTextPosition(AbstractButton.CENTER);
        lampButton.setHorizontalTextPosition(AbstractButton.TRAILING);
        lampButton.setToolTipText("Add a street lamp to the map.");
        lampButton.setFont(buttonFont);
        lampButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                selectAddLamp();
            }
        });
        lampButton.setEnabled(false);
        lampButton.setFocusable(false);
        this.add(lampButton);

        treeButton = new JButton(" Tree        ", treeIcon);
        treeButton.setVerticalTextPosition(AbstractButton.CENTER);
        treeButton.setHorizontalTextPosition(AbstractButton.TRAILING);
        treeButton.setToolTipText("Add a tree to the map.");
        treeButton.setFont(buttonFont);
        treeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                selectAddTree();
            }
        });
        treeButton.setEnabled(false);
        treeButton.setFocusable(false);
        this.add(treeButton);

        fireHydrantButton = new JButton(" Fire Hydrant", fireHydrantIcon);
        fireHydrantButton.setVerticalTextPosition(AbstractButton.CENTER);
        fireHydrantButton.setHorizontalTextPosition(AbstractButton.TRAILING);
        fireHydrantButton.setToolTipText("Add a fire hydrant to the map.");
        fireHydrantButton.setFont(buttonFont);
        fireHydrantButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                selectAddHydrant();
            }
        });
        fireHydrantButton.setEnabled(false);
        fireHydrantButton.setFocusable(false);
        this.add(fireHydrantButton);
        
        eraseButton = new JButton(" Erase       ", eraseIcon);
        eraseButton.setVerticalTextPosition(AbstractButton.CENTER);
        eraseButton.setHorizontalTextPosition(AbstractButton.TRAILING);
        eraseButton.setToolTipText("Delete objects from the map.");
        eraseButton.setFont(buttonFont);
        eraseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                selectErase();
            }
        });
        eraseButton.setEnabled(false);
        eraseButton.setFocusable(false);
        this.add(eraseButton);
        
        selectButton = new JButton(" Select      ", selectIcon);
        selectButton.setVerticalTextPosition(AbstractButton.CENTER);
        selectButton.setHorizontalTextPosition(AbstractButton.TRAILING);
        selectButton.setToolTipText("Box-select a group of objects.");
        selectButton.setFont(buttonFont);
        selectButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                selectSelect();
            }
        });
        selectButton.setEnabled(false);
        selectButton.setFocusable(false);
        this.add(selectButton);
    }
    
    
    // selectors
    public void selectPointer() {
        pointerButton.setSelected(true);
        buildingButton.setSelected(false);
        roadButton.setSelected(false);
        roadPathButton.setSelected(false);
        lampButton.setSelected(false);
        treeButton.setSelected(false);
        fireHydrantButton.setSelected(false);
        eraseButton.setSelected(false);
        selectButton.setSelected(false);
        selection = MenuSelection.POINTER;
    }
    public void selectAddBuilding() {
        buildingButton.setSelected(true);
        pointerButton.setSelected(false);
        roadButton.setSelected(false);
        roadPathButton.setSelected(false);
        lampButton.setSelected(false);
        treeButton.setSelected(false);
        fireHydrantButton.setSelected(false);
        eraseButton.setSelected(false);
        selectButton.setSelected(false);
        selection = MenuSelection.BUILDING;
    }
    public void selectAddRoad() {
        roadButton.setSelected(true);
        pointerButton.setSelected(false);
        buildingButton.setSelected(false);
        roadPathButton.setSelected(false);
        lampButton.setSelected(false);
        treeButton.setSelected(false);
        fireHydrantButton.setSelected(false);
        eraseButton.setSelected(false);
        selectButton.setSelected(false);
        selection = MenuSelection.ROAD_INTERSECTION;
    }
    public void selectAddRoadPath() {
        roadPathButton.setSelected(true);
        pointerButton.setSelected(false);
        buildingButton.setSelected(false);
        roadButton.setSelected(false);
        lampButton.setSelected(false);
        treeButton.setSelected(false);
        fireHydrantButton.setSelected(false);
        eraseButton.setSelected(false);
        selectButton.setSelected(false);
        selection = MenuSelection.ROAD_PATH;
    }
    public void selectAddLamp() {
        lampButton.setSelected(true);
        pointerButton.setSelected(false);
        buildingButton.setSelected(false);
        roadButton.setSelected(false);
        roadPathButton.setSelected(false);
        treeButton.setSelected(false);
        fireHydrantButton.setSelected(false);
        eraseButton.setSelected(false);
        selectButton.setSelected(false);
        selection = MenuSelection.LAMP;
    }
    public void selectAddTree() {
        treeButton.setSelected(true);
        pointerButton.setSelected(false);
        buildingButton.setSelected(false);
        roadButton.setSelected(false);
        roadPathButton.setSelected(false);
        lampButton.setSelected(false);
        fireHydrantButton.setSelected(false);
        eraseButton.setSelected(false);
        selectButton.setSelected(false);
        selection = MenuSelection.TREE;
    }
    public void selectAddHydrant() {
        fireHydrantButton.setSelected(true);
        pointerButton.setSelected(false);
        buildingButton.setSelected(false);
        roadButton.setSelected(false);
        roadPathButton.setSelected(false);
        lampButton.setSelected(false);
        treeButton.setSelected(false);
        eraseButton.setSelected(false);
        selectButton.setSelected(false);
        selection = MenuSelection.HYDRANT;
    }
    public void selectErase() {
        eraseButton.setSelected(true);
        pointerButton.setSelected(false);
        buildingButton.setSelected(false);
        roadButton.setSelected(false);
        roadPathButton.setSelected(false);
        lampButton.setSelected(false);
        treeButton.setSelected(false);
        fireHydrantButton.setSelected(false);
        selectButton.setSelected(false);
        selection = MenuSelection.ERASE;
    }
    public void selectSelect() {
        selectButton.setSelected(true);
        pointerButton.setSelected(false);
        buildingButton.setSelected(false);
        roadButton.setSelected(false);
        roadPathButton.setSelected(false);
        lampButton.setSelected(false);
        treeButton.setSelected(false);
        fireHydrantButton.setSelected(false);
        eraseButton.setSelected(false);
        selection = MenuSelection.SELECT;
    }
    
    
    // switch this menu to editor mode (enabled buttons and button events)
    public void setEditMode(){
        pointerButton.setEnabled(true);
        buildingButton.setEnabled(true);
        roadButton.setEnabled(true);
        roadPathButton.setEnabled(true);
        lampButton.setEnabled(true);
        treeButton.setEnabled(true);
        fireHydrantButton.setEnabled(true);
        eraseButton.setEnabled(true);
        selectButton.setEnabled(true);
        selectPointer();
    }
    
    
    // get the current editor selection (which button is selected)
    public MenuSelection getCurSelection(){
        return this.selection;
    }
    
    
    // returns an image icon (attempts go get it from the resources folder)
    private ImageIcon getIcon(String src){
        URL imgURL = this.getClass().getClassLoader().getResource(src);
        if(imgURL == null){
            System.out.println("ERROR: Can't load \"" + src + "\".");
            System.exit(-1);
        }
        ImageIcon icon = new ImageIcon(imgURL);
        Image img = icon.getImage();
        Image newImg = img.getScaledInstance(34, 34, Image.SCALE_SMOOTH);
        icon = new ImageIcon(newImg);
        return icon;
    }
}
