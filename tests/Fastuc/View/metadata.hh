<?hh // strict

return array
(
	'profile/view' => array
	(
		'title' => function( Map<string, mixed> $params )
		{
			return sprintf( 'Information about %s', $params['itemName'] );
		},
	)
);

