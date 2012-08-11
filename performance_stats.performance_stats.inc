<?php
/**
 * @file
 * Provide stats to report on the performance-stats page.
 */


/**
 * Implements hook_performance_stats.
 */
function performance_stats_performance_stats() {
  $stats = array();
  if (function_exists('apc_cache_info')) {
    $apc_opcode = apc_cache_info('opcode', 1);
    $apc_info = apc_sma_info();
    $stats[] = array(
      'title' => 'APC: Memory Usage',
      'type' => 'pie',
      'name' => 'apc_free',
      'data' => array(
        'Used' => round($apc_opcode['mem_size'] / pow(1024, 2), 2),
        'Free' => round($apc_info['avail_mem'] / pow(1024, 2), 2),
      ),
      'columns' => array(
        'string' => 'Usage',
        'number' => 'Mb',
      )
    );
    $stats[] = array(
      'title' => 'APC: Hits & Misses',
      'type' => 'column',
      'name' => 'apc_hitmiss',
      'options' => array(
        'legend' => 'none',
      ),
      'data' => array(
        'Hits' => $apc_opcode['num_hits'],
        'Misses' => $apc_opcode['num_misses'],
      ),
      'columns' => array(
        'string' => 'Usage',
        'number' => 'Mb',
      )
    );
  }

  if (class_exists('Redis')) {
    $redis = new Redis();
    $redis_host = variable_get('redis_client_host', '127.0.0.1');
    $redis_port = variable_get('redis_client_port', 6379);
    $redis->connect($redis_host, $redis_port);

    $redis_info = $redis->info();
    $redis_config = $redis->config('GET', '*');

    $stats[] = array(
      'title' => 'Redis: Memory Usage',
      'type' => 'pie',
      'name' => 'redis_free',
      'data' => array(
        'Used' => round($redis_info['used_memory'] / pow(1024, 2), 2),
        'Free' => round($redis_config['maxmemory'] / pow(1024, 2), 2),
      ),
      'columns' => array(
        'string' => 'Usage',
        'number' => 'Mb',
      )
    );

    $stats[] = array(
      'title' => 'Redis: Hits & Misses',
      'type' => 'column',
      'name' => 'redis_hitmiss',
      'options' => array(
        'legend' => 'none',
      ),
      'data' => array(
        'Hits' => $redis_info['keyspace_hits'],
        'Misses' => $redis_info['keyspace_misses'],
      ),
      'columns' => array(
        'string' => 'Usage',
        'number' => 'GETs',
      )
    );
  }

  return $stats;
}
