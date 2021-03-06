<?php

/**
 * @file
 * User Stats is user online sort handler.
 */

/**
 * Is user online sort handler.
 */
class views_handler_sort_is_online extends views_handler_sort {
  function query() {
    $this->ensure_my_table();
    // Currently Views has no support for/information on the {sessions} table.
    $join = new views_join;
    $join->construct('sessions', $this->table_alias, 'uid', 'uid', array());
    $session = $this->query->ensure_table('sessions', NULL, $join);

    // We use an IF for MySQL/PostgreSQL compatibility. Otherwise PostgreSQL
    // would return 'f' and 't'.
    $sql_if_part = "IF((" . REQUEST_TIME . " - $session.timestamp) < " . variable_get('user_block_seconds_online', 900) . ", 1, 0)";
    $this->query->add_orderby(NULL, $sql_if_part, $this->options['order'], $this->table_alias . '_' . $this->field, array('function' => 'max'));
  }
}
