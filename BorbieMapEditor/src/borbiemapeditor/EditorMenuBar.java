package borbiemapeditor;

import java.awt.Event;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.KeyStroke;

/**
 *
 * @author richard
 */
public class EditorMenuBar extends JMenuBar {
    
    
    private final MainWindow mainWindow;
    
    // menu items: file
    private JMenuItem f_newMapImage;
    private JMenuItem f_openMapImage;
    private JMenuItem f_saveMapImage;
    private JMenuItem f_importCoords;
    private JMenuItem f_exportCoords;
    private JMenuItem f_exit;
    
    // menu items: edit
    private JMenuItem e_cut;
    private JMenuItem e_copy;
    private JMenuItem e_paste;
    private JMenuItem e_clearSelected;
    private JMenuItem e_selectAll;
    private JMenuItem e_clearAll;
    private JMenuItem e_preferences;
    
    
    // CONSTRUCTOR: sets up all of the main menu items, and adds appropriate
    //  actions to each of them.
    public EditorMenuBar(final MainWindow mainWindow) {
        super();
        
        this.mainWindow = mainWindow;
        
        
        /*** FILE MENU ***/
        JMenu fileMenu = new JMenu("File");
        
        // open and display an existing map image
        f_newMapImage = new JMenuItem("New Map");
        f_newMapImage.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                JOptionPane.showMessageDialog(mainWindow,
                    "Sorry, this feature is not yet available.",
                    "Super lame!",
                    JOptionPane.WARNING_MESSAGE);
            }
        });
        f_newMapImage.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, Event.CTRL_MASK));
        fileMenu.add(f_newMapImage);
        
        // separator
        fileMenu.addSeparator();
        
        // open and display an existing map image
        f_openMapImage = new JMenuItem("Open Map Image");
        f_openMapImage.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                mainWindow.loadMapImage();
            }
        });
        f_openMapImage.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, Event.CTRL_MASK));
        fileMenu.add(f_openMapImage);
        
        // save the current map image (as an image)
        f_saveMapImage = new JMenuItem("Save Map Image");
        f_saveMapImage.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                JOptionPane.showMessageDialog(mainWindow,
                    "Sorry, this feature is not yet available.",
                    "Super lame!",
                    JOptionPane.WARNING_MESSAGE);
            }
        });
        f_saveMapImage.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, Event.CTRL_MASK));
        f_saveMapImage.setEnabled(false);
        fileMenu.add(f_saveMapImage);
        
        // separator
        fileMenu.addSeparator();
        
        // import a coordinate file to load onto the current map
        f_importCoords = new JMenuItem("Import Coordinates");
        f_importCoords.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                JOptionPane.showMessageDialog(mainWindow,
                    "Sorry, this feature is not yet available.",
                    "Super lame!",
                    JOptionPane.WARNING_MESSAGE);
            }
        });
        f_importCoords.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_I, Event.CTRL_MASK));
        f_importCoords.setEnabled(false);
        fileMenu.add(f_importCoords);
        
        // export the coordinate file from the current map image
        f_exportCoords = new JMenuItem("Export Coordinates");
        f_exportCoords.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                mainWindow.exportCoordinates();
            }
        });
        f_exportCoords.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_E, Event.CTRL_MASK));
        f_exportCoords.setEnabled(false);
        fileMenu.add(f_exportCoords);
        
        // separator
        fileMenu.addSeparator();
        
        // add exit button (quits program when clicked)
        f_exit = new JMenuItem("Exit");
        f_exit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                // TODO: check for save if unsaved file is open
                System.exit(0);
            }
        });
        fileMenu.add(f_exit);
        
        this.add(fileMenu);
        
        
        
        /*** EDIT MENU ***/
        JMenu editMenu = new JMenu("Edit");
        
        // cut button: copy any and all selected objects, and delete them
        e_cut = new JMenuItem("Cut");
        e_cut.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                mainWindow.getMapPanel().cutAllSelected();
            }
        });
        e_cut.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X, Event.CTRL_MASK));
        e_cut.setEnabled(false);
        editMenu.add(e_cut);
        
        // copy button: copy any and all selected objects
        e_copy = new JMenuItem("Copy");
        e_copy.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                mainWindow.getMapPanel().copyAllSelected();
            }
        });
        e_copy.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C, Event.CTRL_MASK));
        e_copy.setEnabled(false);
        editMenu.add(e_copy);
        
        // paste button: paste any and all copied objected
        e_paste = new JMenuItem("Paste");
        e_paste.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                mainWindow.getMapPanel().pasteCopiedObjects();
            }
        });
        e_paste.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_V, Event.CTRL_MASK));
        e_paste.setEnabled(false);
        editMenu.add(e_paste);
        
        // separator
        editMenu.addSeparator();
        
        // select all button: selects all map objects
        e_selectAll = new JMenuItem("Select All");
        e_selectAll.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                mainWindow.getMapPanel().selectAll();
            }
        });
        e_selectAll.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_A, Event.CTRL_MASK));
        e_selectAll.setEnabled(false);
        editMenu.add(e_selectAll);
        
        // clear all (del) button: deletes all selected objects
        e_clearSelected = new JMenuItem("Clear Selected");
        e_clearSelected.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                mainWindow.getMapPanel().deleteAllSelected();
            }
        });
        e_clearSelected.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_DELETE, 0));
        e_clearSelected.setEnabled(false);
        editMenu.add(e_clearSelected);
        
        // separator
        editMenu.addSeparator();
        
        // button to clear all objects off the screen: pops up a confirmation box
        e_clearAll = new JMenuItem("Clear All");
        e_clearAll.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                // confirm, and then call the clear-all function
                String[] options = new String[2];
                options[0] = "Clear All Objects";
                options[1] = "Cancel";
                int answer = JOptionPane.showOptionDialog(
                        mainWindow,
                        "This action will DELETE ALL MAP OBJECTS.\n" +
                        "Are you sure you want to continue?",
                        "Warning: Delete All?",
                        JOptionPane.YES_NO_OPTION,
                        JOptionPane.QUESTION_MESSAGE,
                        null, // no custom icon
                        options,
                        options[1]);
                System.out.println(answer);
                if(answer == 0)
                    mainWindow.getMapPanel().deleteAll();
            }
        });
        e_clearAll.setEnabled(false);
        editMenu.add(e_clearAll);
        
        // separator
        editMenu.addSeparator();
        
        // preferences
        e_preferences = new JMenuItem("Preferences");
        e_preferences.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                PreferencesPanel pref = new PreferencesPanel(mainWindow);
            }
        });
        editMenu.add(e_preferences);
        
        this.add(editMenu);
    }
    
    
    // enable the menu items associated with editor mode (once an image is loaded)
    public void setEditMode(){
        f_saveMapImage.setEnabled(true);
        f_importCoords.setEnabled(true);
        f_exportCoords.setEnabled(true);
        
        e_cut.setEnabled(true);
        e_copy.setEnabled(true);
        e_paste.setEnabled(true);
        e_clearSelected.setEnabled(true);
        e_selectAll.setEnabled(true);
        e_clearAll.setEnabled(true);
    }
}
