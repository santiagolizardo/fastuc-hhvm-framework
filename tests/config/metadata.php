<?hh // strict

return array
(
	'profile/view' => array
	(
		'title' => function( array $params )
		{
			return sprintf( 'Information about %s', $params['itemName'] );
		},
	)
);

