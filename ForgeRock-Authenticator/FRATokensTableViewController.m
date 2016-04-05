/*
 * The contents of this file are subject to the terms of the Common Development and
 * Distribution License (the License). You may not use this file except in compliance with the
 * License.
 *
 * You can obtain a copy of the License at legal/CDDLv1.0.txt. See the License for the
 * specific language governing permission and limitations under the License.
 *
 * When distributing Covered Software, include this CDDL Header Notice in each file and include
 * the License file at legal/CDDLv1.0.txt. If applicable, add the following below the CDDL
 * Header, with the fields enclosed by brackets [] replaced by your own identifying
 * information: "Portions copyright [year] [name of copyright owner]".
 *
 * Copyright 2016 ForgeRock AS.
 *
 * Portions Copyright 2014 Nathaniel McCallum, Red Hat
 */

#import "FRATokensTableViewController.h"
#import "FRATokenCodeViewController.h"
#import "FRAIdentity.h"
#import "FRAIdentityDatabase.h"
#import "FRAOathMechanism.h"

@interface FRATokensTableViewController ()

- (NSArray*)oathMechanismsFromDatabase;

@end

@implementation FRATokensTableViewController {
    FRAIdentityDatabase* database;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    database = [FRAIdentityDatabase singleton];
    self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.tableView reloadData];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Present accounts as a flat list not broken down into sections
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self oathMechanismsFromDatabase].count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    FRATokensTableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:@"TokenCell" forIndexPath:indexPath];
    if (cell.delegate) {
        // TODO: Point existing controller at new mechanism or close existing controller and replace with a new one?
    }
    cell.mechanism = [[self oathMechanismsFromDatabase] objectAtIndex:indexPath.row];
    cell.delegate = [FRATokenCodeViewController controllerForView:cell withMechanism:cell.mechanism];
    cell.delegate.editing = self.tableView.editing;
    return cell;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
    return YES;
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)aTableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
    // Only offer delete option when in edit mode (disables swipe to delete)
    if (self.tableView.editing) {
        return UITableViewCellEditingStyleDelete;
    } else {
        return UITableViewCellEditingStyleNone;
    }
}

- (void)setEditing:(BOOL)editing animated:(BOOL)animated {
    [super setEditing:editing animated:animated];
    for (FRATokensTableViewCell* cell in self.tableView.visibleCells) {
        cell.delegate.editing = editing;
    }
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        FRATokensTableViewCell* cell = [tableView cellForRowAtIndexPath:indexPath];
        if (cell.mechanism) {
            [database removeMechanismWithId:cell.mechanism.uid];
            [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationAutomatic];
        }
    }
}

- (void)tableView:(UITableView*)tableView didSelectRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
    if (!self.tableView.editing) {
        [tableView deselectRowAtIndexPath:indexPath animated:YES];
        FRATokensTableViewCell* cell = [tableView cellForRowAtIndexPath:indexPath];
        [cell.delegate didTouchUpInside];
    }
}

-(void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
    // make table cell separator lines full width (normally, they leave a ~10% gap at the left edge)
    if ([cell respondsToSelector:@selector(setSeparatorInset:)]) {
        [cell setSeparatorInset:UIEdgeInsetsZero];
    }
    if ([cell respondsToSelector:@selector(setLayoutMargins:)]) {
        [cell setLayoutMargins:UIEdgeInsetsZero];
    }
}

-(void)viewDidLayoutSubviews {
    // make table cell separator lines full width (normally, they leave a ~10% gap at the left edge)
    if ([self.tableView respondsToSelector:@selector(setSeparatorInset:)]) {
        [self.tableView setSeparatorInset:UIEdgeInsetsZero];
    }
    if ([self.tableView respondsToSelector:@selector(setLayoutMargins:)]) {
        [self.tableView setLayoutMargins:UIEdgeInsetsZero];
    }
}

- (NSArray*)oathMechanismsFromDatabase {
    NSMutableArray* array = [NSMutableArray array];
    for (FRAIdentity* identity in [database identities]) {
        for (FRAOathMechanism* mechanism in [database mechanismsWithOwner:identity]) {
            [array addObject:mechanism];
        }
    }
    return array;
}

@end