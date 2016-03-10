//
//  ViewController.swift
//  CableCam
//
//  Created by Etienne Pilon on 3/7/16.
//  Copyright © 2016 Etienne Pilon. All rights reserved.
//

import UIKit
import CoreBluetooth

class ViewController: UIViewController, CBCentralManagerDelegate, CBPeripheralDelegate {
    
    @IBOutlet weak var sendBT: UIButton!
    private var centralManager: CBCentralManager?
    // Found with print(peripheral.identifier)
    private let UUID: CBUUID = CBUUID(string: "33CBB2D4-55EC-C08B-159D-078CD60B7C72")
    
    override func viewDidLoad() {
        super.viewDidLoad()
        print(UUID)
        centralManager = CBCentralManager(delegate: self, queue: nil)
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
        centralManager?.stopScan()
    }
    
    @IBAction func sendBT(sender: UIButton){
        print("Test")
    }
    
}

extension ViewController{
    func centralManagerDidUpdateState(central: CBCentralManager){
        if central.state.rawValue == CBCentralManagerState.PoweredOn.rawValue{
            print("Power On")
            scanForPeripherals()
        }
        else if central.state.rawValue == CBCentralManagerState.PoweredOff.rawValue{
            print("Power off")
        }
        else if central.state.rawValue == CBCentralManagerState.Resetting.rawValue{
            print("Resetting...")
        }
        else if central.state.rawValue == CBCentralManagerState.Unauthorized.rawValue{
            print("Unauthorized")
        }
        else if central.state.rawValue == CBCentralManagerState.Unknown.rawValue {
            print("Unknown")
        }
        
    }
    func scanForPeripherals(){
        print("Scanning for peripherals")
        centralManager?.scanForPeripheralsWithServices(nil, options: nil)
    }
    func centralManager(central: CBCentralManager, didFailToConnectPeripheral peripheral: CBPeripheral, error: NSError?) {
        if let e = error{
            print("Error: \(e.code)")
        }
        print("Fail to connect peripheral")
    }
    func centralManager(central: CBCentralManager, didConnectPeripheral peripheral: CBPeripheral) {
        print("Peripheral connected")
    }
    func centralManager(central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: NSError?) {
        print("Peripheral disconnected")
    }
    func centralManager(central: CBCentralManager, didDiscoverPeripheral peripheral: CBPeripheral, advertisementData: [String : AnyObject], RSSI: NSNumber) {
        print("Find peripheral \(RSSI)")
        centralManager?.stopScan()
        centralManager?.connectPeripheral(peripheral, options: nil)
        print(peripheral.description)
        print(UUID)
        peripheral.delegate = self
    }
}
extension ViewController{
    
}